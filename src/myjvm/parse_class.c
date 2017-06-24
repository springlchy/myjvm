/**
 * +-----------------------------------------------------------------+
 * |  myjvm writing a Java virtual machine step by step (C version)  |
 * +-----------------------------------------------------------------+
 * |  Author: springlchy <sisbeau@126.com>  All Rights Reserved      |
 * +-----------------------------------------------------------------+
 */

#include<stdio.h>
#include<stdlib.h>
#include <errno.h>
#include <error.h>

#include "structs.h"
#include "utils.h"
#include "op_core.h"
#include "opcode.c"
#include "class_hash.h"

/* the directory to hold the test class and the class from jdk */
char *class_dir="E:/javaweb/test/src/";

#define ATTR_CODE 0x0001
#define ATTR_LINE_NUMBER_TABLE 0x0001
#define ATTR_LOCAL_VARIABLE_TABLE 0x0002;
#define ATTR_LOCAL_VARIABLE_TYPE_TABLE 0x0004


#define GET_METHODREF_FROM_INDEX(pclass, mindex) ((CONSTANT_Methodref_info*)(pclass->constant_pool[mindex]))
#define IS_THIS_CLASS_METHOD(pclass, mindex) ((GET_METHODREF_FROM_INDEX(pclass,mindex))->class_index == pclass->this_class)
#define IS_SUPER_CLASS_METHOD(pclass, mindex) ((GET_METHODREF_FROM_INDEX(pclass,mindex))->class_index == pclass->super_class)
#define GET_REAL_METHOD_FROM_REF(method_ref) (method_info*)(method_ref->ref_addr)
#define GET_REAL_METHOD_FROM_INDEX(pclass, mindex) (method_info*)(((CONSTANT_Methodref_info*)(pclass->constant_pool[mindex]))->ref_addr)
#define GET_CODE_FROM_METHOD(method) (Code_attribute*)(method->code_attribute_addr)

#define DEFINE_CONSTANT_POOL_VARS()     CONSTANT_Utf8_info *utf8_info;\
CONSTANT_Integer_info *int_info;\
CONSTANT_Float_info *float_info;\
CONSTANT_Long_info *long_info;\
CONSTANT_Double_info *double_info;\
CONSTANT_Class_info *class_info;\
CONSTANT_String_info *str_info;\
CONSTANT_Fieldref_info *f_info;\
CONSTANT_Methodref_info *m_info;\
CONSTANT_InterfaceMethodref_info *interm_info;\
CONSTANT_NameAndType_info *nt_info;\
CONSTANT_MethodHandle_info *mh_info;\
CONSTANT_MethodType_info *mt_info;\
CONSTANT_InvokeDynamic_info *inv_info


#define get_utf8(pool) ((CONSTANT_Utf8_info*)(pool))->bytes
#define get_class_name(pools, index) get_utf8(pools[(((CONSTANT_Class_info*)(pools[index]))->name_index)])

#define printf_name_and_type(pools,pool) fprintf(stderr, "%s:%s", get_utf8(pools[((CONSTANT_NameAndType_info*)pool)->name_index]), get_utf8(pools[((CONSTANT_NameAndType_info*)pool)->descriptor_index]))

#define printf_numeric(index, tag, v) fprintf(stderr, "#%d\t%s\t\t", index, cpTypeMap[tag])
#define printf_one_ref(index, tag, pool, ref) fprintf(stderr, "#%d\t%s\t #%d\t// %s\n", index, cpTypeMap[tag], ref, get_utf8(pool))
#define printf_ref_nt(index, tag, obj, pools) fprintf(stderr, "#%d\t%s\t #%d.#%d // %s.", index, cpTypeMap[tag], obj->class_index, obj->name_and_type_index, get_class_name(pools, obj->class_index))

#define emalloc(TYPE, VARNAME) VARNAME = (TYPE*)malloc(sizeof(TYPE))
#define IS_MAIN_METHOD(pclass, method) (strcmp(get_utf8(pclass->constant_pool[method->name_index]), "main") == 0)
#define GET_FIELD_TYPE(pclass,fieldref) get_utf8(pclass->constant_pool[((CONSTANT_NameAndType_info*)(pclass->constant_pool[fieldref->name_and_type_index]))->descriptor_index])
#define IS_CLINIT_METHOD(pclass, method) (strcmp(get_utf8(pclass->constant_pool[method->name_index]), "<clinit>") == 0)
#define get_this_class_name(pclass) get_utf8(pclass->constant_pool[((CONSTANT_Class_info*)(pclass->constant_pool[pclass->this_class]))->name_index])
#define get_super_class_name(pclass) get_utf8(pclass->constant_pool[((CONSTANT_Class_info*)(pclass->constant_pool[pclass->super_class]))->name_index])

void showConstantPool(Class *pclass);
void* readLineNumberTable(FILE *fp);
void* readLocalVariableTable(FILE *fp);
void* readLocalVariableTypeTable(FILE *fp);
void setThisClassFieldIndex(Class *pclass);
Code_attribute* parseCodeAttribute(FILE *fp, Class *pclass);

void printMethodrefInfo(Class* pclass, CONSTANT_Methodref_info* method_ref)
{
    cp_info cp = pclass->constant_pool;
    CONSTANT_Class_info* class_info;
    CONSTANT_NameAndType_info* nt_info;
    class_info = (CONSTANT_Class_info*)(cp[method_ref->class_index]);
    nt_info = (CONSTANT_NameAndType_info*)(cp[method_ref->name_and_type_index]);

    printf("method: %s::%s.%s\n", get_utf8(cp[class_info->name_index]),\
            get_utf8(cp[nt_info->name_index]),\
            get_utf8(cp[nt_info->descriptor_index]));

}

void classNotFound(const char* class_name)
{
    printf(stderr, "Error! Cannot load class: %s", class_name);
    exit(1);
}

void parseConstantPool(FILE *fp, Class* pclass)
{
    DEFINE_CONSTANT_POOL_VARS();

    ushort pool_count = readUShort(fp);
    pclass->constant_pool_count = pool_count;
    pclass->constant_pool = (void**)malloc(sizeof(void*) * (pool_count+1));
    printf("position: %d\n", ftell(fp));
    printf("constant_pool_count: %d\n", pclass->constant_pool_count);

    memset(pclass->constant_pool, 0, (pool_count+1)*4);

    ushort index = 0;
    uchar utag;
    ushort tag;
    while (++index < pool_count) {
        utag = readU1(fp);
        tag = (ushort)utag;
        //printf("index=%d, tag=%d\n", index, tag);
        switch (tag) {
            case CONSTANT_Utf8:
                emalloc(CONSTANT_Utf8_info, utf8_info);
                utf8_info->tag = tag;
                utf8_info->length = readUShort(fp);
                utf8_info->bytes = (char*)malloc(sizeof(char) * utf8_info->length+1);
                memset(utf8_info->bytes, 0, utf8_info->length+1);
                readBytes(fp, utf8_info->bytes, utf8_info->length);
                pclass->constant_pool[index] = (void*)utf8_info;

                break;
            case CONSTANT_Integer:
                emalloc(CONSTANT_Integer_info, int_info);
                int_info->tag = tag;
                int_info->value = readInt(fp);
                pclass->constant_pool[index] = (void*)int_info;

                break;
            case CONSTANT_Float:
                emalloc(CONSTANT_Float_info, float_info);
                float_info->tag = tag;
                float_info->value = readFloat(fp);
                pclass->constant_pool[index] = (void*)float_info;

                break;
            case CONSTANT_Long:
                emalloc(CONSTANT_Long_info, long_info);
                long_info->tag = tag;
                long_info->value = readLong(fp);
                pclass->constant_pool[index] = (void*)long_info;
                index++;
                //readU1(fp);
                //readU4(fp);
                break;
            case CONSTANT_Double:
                emalloc(CONSTANT_Double_info, double_info);
                double_info->tag = tag;
                double_info->value = readDouble(fp);
                pclass->constant_pool[index] = (void*)double_info;
                index++;
                //readU1(fp);
                //readU4(fp);
                break;
            case CONSTANT_Class:
                emalloc(CONSTANT_Class_info, class_info);
                memset(class_info, 0, sizeof(CONSTANT_Class_info));
                class_info->tag = tag;
                class_info->name_index = readUShort(fp);
                class_info->pclass = NULL;
                pclass->constant_pool[index] = (void*)class_info;

                break;
            case CONSTANT_String:
                emalloc(CONSTANT_String_info, str_info);
                str_info->tag = tag;
                str_info->string_index = readUShort(fp);
                pclass->constant_pool[index] = (void*)str_info;

                break;
            case CONSTANT_Fieldref:
                emalloc(CONSTANT_Fieldref_info, f_info);
                f_info->tag = tag;
                f_info->class_index = readUShort(fp);
                f_info->name_and_type_index = readUShort(fp);
                pclass->constant_pool[index] = (void*)f_info;
                f_info->ftype = 0;

                break;
            case CONSTANT_Methodref:
                emalloc(CONSTANT_Methodref_info, m_info);
                m_info->tag = tag;
                m_info->class_index = readUShort(fp);
                m_info->name_and_type_index = readUShort(fp);
                //m_info->args_len = -1;
                pclass->constant_pool[index] = (void*)m_info;
                m_info->ref_addr = NULL;
                m_info->mtable = NULL;

                break;
            case CONSTANT_InterfaceMethodref:
                emalloc(CONSTANT_InterfaceMethodref_info, interm_info);
                interm_info->tag = tag;
                interm_info->class_index = readUShort(fp);
                interm_info->name_and_type_index = readUShort(fp);
                pclass->constant_pool[index] = (void*)interm_info;

                break;
            case CONSTANT_NameAndType:
                emalloc(CONSTANT_NameAndType_info, nt_info);
                nt_info->tag = tag;
                nt_info->name_index = readUShort(fp);
                nt_info->descriptor_index = readUShort(fp);
                pclass->constant_pool[index] = (void*)nt_info;

                break;
            case CONSTANT_MethodHandle:
                emalloc(CONSTANT_MethodHandle_info, mh_info);
                mh_info->tag = tag;
                mh_info->reference_kind = readU1(fp);
                mh_info->reference_index = readUShort(fp);
                pclass->constant_pool[index] = (void*)mh_info;

                break;
            case CONSTANT_MethodType:
                emalloc(CONSTANT_MethodType_info, mt_info);
                mt_info->tag = tag;
                mt_info->descriptor_index = readUShort(fp);
                pclass->constant_pool[index] = (void*)mt_info;

                break;
            case CONSTANT_InvokeDynamic:
                emalloc(CONSTANT_InvokeDynamic_info, inv_info);
                inv_info->tag = tag;
                inv_info->name_and_type_index = readUShort(fp);
                inv_info->bootstrap_method_attr_index = readUShort(fp);
                pclass->constant_pool[index] = (void*)inv_info;

                break;
            default:
                printf("Error tag: %d, at %ld\n", tag, ftell(fp));
                break;
        }
    }
}

void parseInterface(FILE *fp, Class *pclass)
{
    ushort inter_count = readUShort(fp);
    pclass->interface_count = inter_count;

    ushort index = 0;
    if (inter_count > 0) {
        pclass->interfaces = (ushort*)malloc(sizeof(ushort) * inter_count);
        while (index++ < inter_count) {
            pclass->interfaces[index] = readUShort(fp);
        }
    } else {
        pclass->interfaces = NULL;
    }
}

void parseFields(FILE *fp, Class *pclass)
{
    char ftype;
    ushort last_index=0;
    ushort static_last_index = 0;
    ushort fcount = readUShort(fp);
    pclass->fields_count = fcount;

    ushort index = 0;
    if (fcount > (ushort)0) {
        pclass->fields = (field_info**)malloc(sizeof(field_info*) * fcount);
        field_info *tmp_field;
        attribute_info *tmp_attr;

        while (index < fcount) {
            tmp_field = (field_info*)malloc(sizeof(field_info));
            tmp_field->access_flags = readUShort(fp);
            tmp_field->name_index = readUShort(fp);
            tmp_field->descriptor_index = readUShort(fp);
            tmp_field->attributes_count = readUShort(fp);

            // parse field type and set index
            ftype = *(char*)(get_utf8(pclass->constant_pool[tmp_field->descriptor_index]));
            tmp_field->ftype = ftype;

            if (NOT_ACC_STATIC(tmp_field->access_flags)) {
                tmp_field->findex = last_index;
                if (ftype == 'J' || ftype == 'D') {
                    last_index+=2;
                } else {
                    last_index+=1;
                }
            } else {
                tmp_field->findex = static_last_index;
                if (ftype == 'J' || ftype == 'D') {
                    static_last_index+=2;
                } else {
                    static_last_index+=1;
                }
            }

            // End
            printf("attributes_count_position: %ld\n", ftell(fp));

            ushort aindex = 0;
            tmp_field->attributes = (attribute_info**)malloc(sizeof(attribute_info*) * tmp_field->attributes_count);
            while (aindex < tmp_field->attributes_count) {
                tmp_attr = (attribute_info*)malloc(sizeof(attribute_info));
                tmp_attr->attribute_name_index = readUShort(fp);
                tmp_attr->attribute_length = readUInt(fp);
                tmp_attr->info = (char*)malloc(sizeof(char)*tmp_attr->attribute_length);
                readBytes(fp, tmp_attr->info, tmp_attr->attribute_length);

                tmp_field->attributes[aindex] = tmp_attr;

                aindex++;
            }
            pclass->fields[index] = tmp_field;

            index++;
        }
    }

    pclass->fields_size = last_index;
    pclass->parent_fields_size = -1;

    pclass->static_field_size = static_last_index;
    pclass->static_fields = (char*)malloc(sizeof(char) * ((static_last_index+1)<<2));
}

int parseMethodArgs(Class* pclass, ushort descriptor_index)
{
    short args_len = 0, args_count=0;
    char c;
    char* args_desc = get_utf8(pclass->constant_pool[descriptor_index]);
    printf("args_desc=%s\n", args_desc);
    args_desc++;
    while((c = args_desc[0]) != ')') {
        printf("%c\n", c);
        switch (c) {
            case 'B':
            case 'C':
            case 'F':
            case 'I':
            case 'S':
            case 'Z':
                args_len+=SZ_INT;
                args_count++;
                ++args_desc;
                break;
            case 'D':
            case 'J':
                args_len+=SZ_LONG;
                args_count++;
                ++args_desc;
                break;
            case 'L':
                args_len+=SZ_INT;
                args_desc++;
                while(*args_desc != ';') {
                    args_desc++;
                }
                args_desc++;
                args_count++;
                break;
            case '[':
                args_len+=SZ_INT;
                //args_desc++;
                while(*args_desc == '[') {
                    args_desc++;
                }
                if (*args_desc == 'L') {
                    args_desc++;
                    while(*args_desc != ';') {
                        args_desc++;
                    }
                    //args_desc++;
                }
                args_desc++;
                args_count++;
                break;
            default:
                args_desc++;
                break;
        }
    }

    return args_len;
}
void displayMethods(int index, method_info *method, Class *pclass)
{
    FILE *fp;
    if (strcmp(get_this_class_name(pclass), "java/util/Arrays") == 0) {
        fp = fopen("D:/methods.txt", "a+");
        if (fp) {
            fprintf(fp, "index=%d, method=%p\n", index, method);
            fclose(fp);
        }
    }
}

void parseMethods(FILE *fp, Class *pclass)
{
    ushort mcount = readUShort(fp);
    ushort index = 0;
    pclass->methods_count = mcount;
    debug("methods_count=%d", mcount);
    if (mcount > (ushort)0) {
        pclass->methods = (method_info**)malloc(sizeof(method_info*) * mcount);
        method_info *tmp_method;
        attribute_info *tmp_attr;

        while (index < mcount) {
            printf("malloc tmp_method\n");
            tmp_method = (method_info*)malloc(sizeof(method_info));
            if (tmp_method == NULL) {
                printf("malloc error method\n");
                exit(3);
            }
            tmp_method->access_flags = readUShort(fp);
            tmp_method->name_index = readUShort(fp);
            tmp_method->descriptor_index = readUShort(fp);
            tmp_method->attributes_count = readUShort(fp);

            fprintf(stderr, "method=%s", get_utf8(pclass->constant_pool[tmp_method->name_index]));

            tmp_method->args_len = parseMethodArgs(pclass, tmp_method->descriptor_index);

            ushort aindex = 0;
            tmp_method->attributes = (attribute_info**)malloc(sizeof(attribute_info*) * tmp_method->attributes_count);
            while (aindex < tmp_method->attributes_count) {
                printf("malloc tmp_attr\n");
                tmp_attr = (attribute_info*)malloc(sizeof(attribute_info));
                if (tmp_attr == NULL) {
                    printf("malloc tmp-attr error\n");
                    exit(3);
                }
                tmp_attr->attribute_name_index = readUShort(fp);
                tmp_attr->attribute_length = readUInt(fp);
                tmp_attr->info = (void*)malloc(sizeof(char)*tmp_attr->attribute_length);

                if (strcmp(get_utf8(pclass->constant_pool[tmp_attr->attribute_name_index]), "Code") == 0) {
                    tmp_attr->info = parseCodeAttribute(fp, pclass);
                    printf("errno=%d, errstr=%s\n", errno, strerror(errno));
                    printf("tmp_attr->info=%p, code_attribute_addr=%p\n", tmp_attr->info, tmp_method->code_attribute_addr);
                    tmp_method->code_attribute_addr = tmp_attr->info; // save code attribute address
                } else {
                    printf("readBytes\n");
                    readBytes(fp, (char*)(tmp_attr->info), tmp_attr->attribute_length);
                }
                printf("tmp_method=%p\n", tmp_method);
                tmp_method->attributes[aindex] = tmp_attr;
                printf("index=%d, tmp_method=%p\n", index, tmp_method);
                aindex++;
            }

            pclass->methods[index] = tmp_method;
            index++;

            displayMethods(index, tmp_method, pclass);
        }
    }
}

void parseAttributes(FILE *fp, Class *pclass)
{
    ushort attr_count = readUShort(fp);
    void* code_attr;
    pclass->attributes_count = attr_count;

    if (attr_count > 0) {
        attribute_info *tmp_attr;
        ushort aindex = 0;
        pclass->attributes = (attribute_info**)malloc(sizeof(attribute_info*) * attr_count);

        while (aindex < attr_count) {
            tmp_attr = (attribute_info*)malloc(sizeof(attribute_info));
            tmp_attr->attribute_name_index = readUShort(fp);
            printf("attr name at: %d, %d\n", ftell(fp), tmp_attr->attribute_name_index);

            tmp_attr->attribute_length = readUInt(fp);
            if (strcmp(get_utf8(pclass->constant_pool[tmp_attr->attribute_name_index]), "Code") == 0) {
                code_attr = parseCodeAttribute(fp, pclass);
                printf("tmp_attr->info=%p, code_attr=%p\n", tmp_attr->info, code_attr);
                tmp_attr->info = (char*)code_attr;
                printf("after read codeattr: errno=%d, errstr=%s\n", errno, strerror(errno));
            } else {
                printf("attr_len=%d\n", tmp_attr->attribute_length);
                tmp_attr->info = (char*)malloc(sizeof(char) * (tmp_attr->attribute_length));
                readBytes(fp, (char*)(tmp_attr->info), tmp_attr->attribute_length);
            }
            printf("errno=%d, errstr=%s\n", errno, strerror(errno));
            pclass->attributes[aindex] = tmp_attr;
            //printf("attr_name_index: %d\n", tmp_attr->attribute_name_index);
            printf("errno=%d, errstr=%s\n", errno, strerror(errno));
            aindex++;
        }
    }
}
void readOtherCodeAttribute(FILE *fp, Class *pclass)
{
    int attr_len = readUInt(fp);
    printf("attr_len=%d, fp=%ld\n", attr_len, ftell(fp));
    fseek(fp, attr_len, SEEK_CUR);
}

Code_attribute* parseCodeAttribute(FILE *fp, Class *pclass)
{
    fprintf(stderr, "-----------code begin-----------------\n");
    Code_attribute *code_attr;
    uchar *pcode;
    uchar *pcode_end;
    uchar op;
    OPENV env;

    emalloc(Code_attribute, code_attr);
    code_attr->attribute_type = ATTR_CODE;
    code_attr->max_stack = readUShort(fp);
    code_attr->max_locals = readUShort(fp);
    code_attr->code_length = readUInt(fp);
    code_attr->code = (uchar*)malloc(sizeof(uchar) * code_attr->code_length);

    readBytes(fp, code_attr->code, code_attr->code_length); //code is here

    // Begin parse code
    pcode = code_attr->code;
    pcode_end = pcode + code_attr->code_length;
    env.pc = pcode;
    env.pc_start = pcode;

    while(env.pc < pcode_end) {
        op = env.pc[0];
        fprintf(stderr, "%4d: %s ", env.pc-pcode, jvm_instructions[op].code_name);
        env.pc+=1;

        jvm_instructions[op].pre_action(&env);
        fprintf(stderr, "\n");
    }
    // End parse code

    code_attr->exception_table_length = readUShort(fp);
    if (code_attr->exception_table_length > 0) {
        code_attr->exceptions = (exception_table*)malloc(sizeof(exception_table) * code_attr->exception_table_length);
        ushort ex_index = 0;
        while (ex_index < code_attr->exception_table_length) {
            code_attr->exceptions[ex_index].start_pc = readUShort(fp);
            code_attr->exceptions[ex_index].end_pc = readUShort(fp);
            code_attr->exceptions[ex_index].handler_pc = readUShort(fp);
            code_attr->exceptions[ex_index].catch_type = readUShort(fp);

            ex_index++;
        }
    }

    code_attr->attributes_count = readUShort(fp);
    if (code_attr->attributes_count > 0) {
        code_attr->attributes = (attribute_info**)malloc(sizeof(attribute_info*) * code_attr->attributes_count);
        ushort attr_index = 0;
        while (attr_index < code_attr->attributes_count) {
            ushort attr_name_index = readUShort(fp);
            char *attr_type_str = get_utf8(pclass->constant_pool[attr_name_index]);
            if (strcmp(attr_type_str, "LineNumberTable") == 0) {
                code_attr->attributes[attr_index] = readLineNumberTable(fp);
            } else if (strcmp(attr_type_str, "LocalVariableTable") == 0) {
                code_attr->attributes[attr_index] = readLocalVariableTable(fp);
            } else if (strcmp(attr_type_str, "LocalVariableTypeTable") == 0) {
                code_attr->attributes[attr_index] = readLocalVariableTypeTable(fp);
            } else {
                debug("skip read attribute: %s", attr_type_str);
                printf("errno=%d, errorstr=%s", errno, strerror(errno));

                readOtherCodeAttribute(fp, pclass);
                printf("errno=%d, errorstr=%s", errno, strerror(errno));
            }

            attr_index++;
        }
    }

    fprintf(stderr, "-----------code end-----------------\n");
    return code_attr;
}

void* readLineNumberTable(FILE *fp)
{
    LineNumberTable_attribute *attr;
    emalloc(LineNumberTable_attribute, attr);
    attr->attribute_type = ATTR_LINE_NUMBER_TABLE;
    attr->attribute_length = readUInt(fp);
    attr->table_length = readUShort(fp);

    if (attr->table_length > 0) {
        ushort aindex = 0;
        attr->tables = (line_number_table*)malloc(sizeof(line_number_table) * attr->table_length);
        while (aindex < attr->table_length) {
            attr->tables[aindex].start_pc = readUShort(fp);
            attr->tables[aindex].line_number = readUShort(fp);

            aindex++;
        }
    }

    return (void*)attr;
}

void* readLocalVariableTable(FILE *fp)
{
    LocalVariableTable_attribute *attr;
    emalloc(LocalVariableTable_attribute, attr);
    attr->attribute_type = ATTR_LOCAL_VARIABLE_TABLE;
    attr->attribute_length = readUInt(fp);
    attr->table_length = readUShort(fp);

    if (attr->table_length > 0) {
        ushort aindex = 0;
        attr->tables = (local_variable_table*)malloc(sizeof(local_variable_table) * attr->table_length);
        while (aindex < attr->table_length) {
            attr->tables[aindex].start_pc = readUShort(fp);
            attr->tables[aindex].length = readUShort(fp);
            attr->tables[aindex].name_index = readUShort(fp);
            attr->tables[aindex].descriptor_index = readUShort(fp);
            attr->tables[aindex].index = readUShort(fp);

            aindex++;
        }
    }

    return (void*)attr;
}

void* readLocalVariableTypeTable(FILE *fp)
{
    LocalVariableTypeTable_attribute *attr;
    emalloc(LocalVariableTypeTable_attribute, attr);
    attr->attribute_type = ATTR_LOCAL_VARIABLE_TABLE;
    attr->attribute_length = readUInt(fp);
    attr->table_length = readUShort(fp);

    if (attr->table_length > 0) {
        ushort aindex = 0;
        attr->tables = (local_variable_type_table*)malloc(sizeof(local_variable_type_table) * attr->table_length);
        while (aindex < attr->table_length) {
            attr->tables[aindex].start_pc = readUShort(fp);
            attr->tables[aindex].length = readUShort(fp);
            attr->tables[aindex].name_index = readUShort(fp);
            attr->tables[aindex].signature_index = readUShort(fp);
            attr->tables[aindex].index = readUShort(fp);

            aindex++;
        }
    }

    return (void*)attr;
}

Class* loadClass(const char *filename)
{
    int fnamelen = 0;
    char *logfile;
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("Cannot open: %s\n", filename);
        printf("errno:%d, errstr:%s\n", errno, strerror(errno));
        exit(1);
        return NULL;
    }

    // log
    fnamelen = strlen(filename);
    logfile = (char*)malloc(fnamelen+1);
    strcpy(logfile, filename);
    logfile[fnamelen] = 0;
    strcpy(logfile + fnamelen - 5, "code");

    Class *pclass = (Class*)malloc(sizeof(Class));
    pclass->parent_class = NULL;

    // step 1: read magic number
    pclass->magic = readUInt(fp);
    //printf("Magic: 0x%X\n", pclass->magic);
    if (pclass->magic != 0xCAFEBABE) {
        printf("Invalid class file!\n");
        exit(1);
    }

    // step2: read version
    pclass->minor_version = readUShort(fp);
    pclass->major_version = readUShort(fp);
    //printf("minor_version: %d\n", pclass->minor_version);
    //printf("major_version: %d\n", pclass->major_version);

    fprintf(stderr, "--------------------------------------------\n");

    // step3: read constant pool
    parseConstantPool(fp, pclass);
    fprintf(stderr, "constant_pool_count: %d\n", pclass->constant_pool_count);
    printf("parse constant pool end\n");
    //showConstantPool(pclass);

    printf("--------------------------------------------\n");
    // step4: read access_flags
    pclass->access_flags = readUShort(fp);
    fprintf(stderr, "access_flag: %04X\t%s\n", pclass->access_flags, formatAccessFlag(pclass->access_flags));

    // step5: this class
    pclass->this_class = readUShort(fp);
    fprintf(stderr, "this_class: #%d\t%s\n", pclass->this_class, get_class_name(pclass->constant_pool, pclass->this_class));

    // step6: super class
    pclass->super_class = readUShort(fp);
    if (pclass->super_class > 0) {
        fprintf(stderr, "super_class: #%d\t%s\n", pclass->super_class, get_class_name(pclass->constant_pool, pclass->super_class));
    }

    fprintf(stderr, "--------------------------------------------\n");
    // step7: read inerfaces
    parseInterface(fp, pclass);
    fprintf(stderr, "interface_count: %d\n", pclass->interface_count);
    //showInterface(pclass);

    fprintf(stderr, "--------------------------------------------\n");
    // step8: read fields
    parseFields(fp, pclass);
    fprintf(stderr, "fields_count: %d\n", pclass->fields_count);
    showFields(pclass);

    fprintf(stderr, "--------------------------------------------\n");
    // step9: read methods
    parseMethods(fp, pclass);
    fprintf(stderr, "methods_count: %d\n", pclass->methods_count);
    showMethods(pclass);

    fprintf(stderr, "--------------------------------------------\n");
    // step10: read attributes
    parseAttributes(fp, pclass);
    //printf("attributes_count: %d\n", pclass->attributes_count);
    //showAttributes(pclass, pclass->attributes, pclass->attributes_count);

    //setThisClassFieldIndex(pclass);

    ((CONSTANT_Class_info*)(pclass->constant_pool[pclass->this_class]))->pclass = pclass;

    fclose(fp);
    printf("class_name=%s, addr=%p", filename, pclass);

    pclass->clinit_runned = 0;
    return pclass;
}

void showConstantPool(Class *pclass)
{
    DEFINE_CONSTANT_POOL_VARS();
    int index = 0;
    cp_info cp = pclass->constant_pool;
    ushort tag = 0;
    while(++index < pclass->constant_pool_count) {
        if (NULL == cp[index]) {
            continue;
        }
        tag = (ushort)(*(char*)cp[index]);
        printf("index=%d, tag=%d\n", index, tag);
        switch (tag) {
            case CONSTANT_Utf8:
                utf8_info = (CONSTANT_Utf8_info*)cp[index];
                fprintf(stderr, "#%d\t%s\t\t%s\n", index, cpTypeMap[tag], utf8_info->bytes);

                break;
            case CONSTANT_Integer:
                int_info = (CONSTANT_Integer_info*)cp[index];
                printf_numeric(index, tag, int_info);
                fprintf(stderr, "%d\n", int_info->value);

                break;
            case CONSTANT_Float:
                float_info = (CONSTANT_Float_info*)cp[index];
                printf_numeric(index, tag, float_info);
                fprintf(stderr, "%f\n", float_info->value);

                break;
            case CONSTANT_Long:
                long_info = (CONSTANT_Long_info*)cp[index];
                printf_numeric(index, tag, long_info);
                fprintf(stderr, "%ld\n", long_info->value);

                break;
            case CONSTANT_Double:
                double_info = (CONSTANT_Double_info*)cp[index];
                printf_numeric(index, tag, double_info);
                fprintf(stderr, "%lf\n", double_info->value);

                break;
            case CONSTANT_Class:
                class_info = (CONSTANT_Class_info*)cp[index];
                //printf("#%d\t%s\t\t #%d\t// %s\n", index, cpType[tag], class_info->name_index, get_utf8(cp[class_info->name_index]));
                printf_one_ref(index, tag, cp[class_info->name_index], class_info->name_index);
                break;
            case CONSTANT_String:
                str_info = (CONSTANT_String_info*)cp[index];
                printf_one_ref(index, tag, cp[str_info->string_index], str_info->string_index);

                break;
            case CONSTANT_Fieldref:
                f_info = (CONSTANT_Fieldref_info*)cp[index];
                printf_ref_nt(index, tag, f_info, cp);
                printf_name_and_type(cp, cp[f_info->name_and_type_index]);
                fprintf(stderr, "\n");

                break;
            case CONSTANT_Methodref:
                m_info = (CONSTANT_Methodref_info*)cp[index];
                printf("minfo=%p,cp=%p, nt_index=%d,nt_info=%p\n", m_info, cp, m_info->name_and_type_index, cp[m_info->name_and_type_index]);
                printf_ref_nt(index, tag, m_info, cp);
                printf("after printf\n");
                nt_info = (CONSTANT_NameAndType_info*)(cp[m_info->name_and_type_index]);
                printf("name_index=%d, desc_index=%d\n", nt_info->name_index, nt_info->descriptor_index);

                printf_name_and_type(cp, cp[m_info->name_and_type_index]);
                fprintf(stderr, "\n");

                break;
            case CONSTANT_InterfaceMethodref:
                interm_info = (CONSTANT_InterfaceMethodref_info*)cp[index];
                printf_ref_nt(index, tag, interm_info, cp);
                printf_name_and_type(cp, cp[interm_info->name_and_type_index]);
                fprintf(stderr, "\n");

                break;
            case CONSTANT_NameAndType:
                nt_info = (CONSTANT_NameAndType_info*)cp[index];
                fprintf(stderr, "#%d\t%s\t\t #%d:#%d // ", index, cpTypeMap[tag], nt_info->name_index, nt_info->descriptor_index);
                printf_name_and_type(cp, nt_info);
                fprintf(stderr, "\n");

                break;
            case CONSTANT_MethodHandle:
                mh_info = (CONSTANT_MethodHandle_info*)cp[index];
                fprintf(stderr, "#%d\t%s\t\t ref_kind=%d,ref_index=%d\n", index, cpTypeMap[tag], mh_info->reference_kind, mh_info->reference_index);

                break;
            case CONSTANT_MethodType:
                mt_info = (CONSTANT_MethodType_info*)cp[index];
                printf_one_ref(index, tag, cp[mt_info->descriptor_index], mt_info->descriptor_index);

                break;
            case CONSTANT_InvokeDynamic:
                inv_info = (CONSTANT_InvokeDynamic_info*)cp[index];
                fprintf(stderr, "#%d\t%s\t\t name_and_type_index=%d,boot_attr_index=%d\n", index, cpTypeMap[tag], inv_info->name_and_type_index, inv_info->bootstrap_method_attr_index);

                break;
            default:
                printf("Error tag: %d\n", tag);
                break;
        }
        fflush(stderr);
    }
}

void showInterface(Class *pclass)
{
    ushort index = 0;
    while (index++ < pclass->interface_count) {
        fprintf(stderr, "interface: #%d\t%s\n", index+1, get_class_name(pclass->constant_pool, pclass->interfaces[index]));
    }
}

void showFields(Class *pclass)
{
    ushort index = 0;

    field_info ** finfos = pclass->fields;

    while (index < pclass->fields_count) {
        fprintf(stderr, "fields[%d]: %s, [name_index=%d]%s:[desc_index=%d]%s\n", index, formatAccessFlag(finfos[index]->access_flags),\
               finfos[index]->name_index,get_utf8(pclass->constant_pool[finfos[index]->name_index]),\
               finfos[index]->descriptor_index,get_utf8(pclass->constant_pool[finfos[index]->descriptor_index]));
        fprintf(stderr, "\tattributes_count: %d\n", finfos[index]->attributes_count);
        showAttributes(pclass, finfos[index]->attributes, finfos[index]->attributes_count);

        index++;
    }
}

void showMethods(Class *pclass)
{
    ushort index = 0;

    method_info ** minfos = pclass->methods;

    while (index < pclass->methods_count) {
        fprintf(stderr, "methods[%d]: %s, [name_index=%d] %s: [desc_index=%d] %s\n", index, formatAccessFlag(minfos[index]->access_flags),\
               minfos[index]->name_index, get_utf8(pclass->constant_pool[minfos[index]->name_index]),\
               minfos[index]->descriptor_index, get_utf8(pclass->constant_pool[minfos[index]->descriptor_index]));
        fprintf(stderr, "\targs_len=%d\n", minfos[index]->args_len);
        fprintf(stderr, "\tattributes_count: %d\n", minfos[index]->attributes_count);
        showAttributes(pclass, minfos[index]->attributes, minfos[index]->attributes_count);

        index++;
    }
}

void showAttributes(Class *pclass, attribute_info **attributes, ushort attribute_count)
{
    ushort index = 0;
    while (index < attribute_count) {
        fprintf(stderr, "\t\tattributes[%d]: #%d // %s\n\t\tlength=%d\n", index, attributes[index]->attribute_name_index,\
               get_utf8(pclass->constant_pool[attributes[index]->attribute_name_index]),\
                attributes[index]->attribute_length);
        index++;
    }
}

void setThisClassFieldIndex(Class *pclass)
{
    ushort index=0;
    uchar flag;
    //char ftype;
    CONSTANT_Fieldref_info* fieldref;
    char ftype;
    ushort last_findex=0;
    while(++index <= pclass->constant_pool_count) {
        if(NULL != pclass->constant_pool[index]) {
            flag = *(char*)(pclass->constant_pool[index]);
            if (flag == CONSTANT_Fieldref) {
                fieldref = (CONSTANT_Fieldref_info*)(pclass->constant_pool[index]);
                if (fieldref->class_index == pclass->this_class) {
                    ftype = *(char*)(GET_FIELD_TYPE(pclass, fieldref));
                    fieldref->findex = last_findex;
                    fieldref->ftype = ftype;
                    if (ftype == 'J' || ftype == 'D') {
                        last_findex+=2;
                    } else {
                        last_findex+=1;
                    }
                }
            }
        }
    }
}

void displayThisClassFieldIndex(Class *pclass)
{
    ushort index=0;
    cp_info cp = pclass->constant_pool;
    field_info *finfo;
    for (index = 0; index < pclass->fields_count; index++) {
        finfo = pclass->fields[index];
        printf("#%d %s findex=%d\n", index, get_utf8(cp[finfo->name_index]), finfo->findex);
    }
}

Class* loadClassFromDisk(const char* class_name)
{
    CONSTANT_Class_info *class_info;
    Class *pclass = NULL;
    char *class_dir="E:/javaweb/test/src/";
    char *class_ext=".class";
    char filename[512];
    memset(filename, 0, 256);
    strcpy(filename, class_dir);
    strcat(filename, class_name);
    strcat(filename, class_ext);

    printf("%s\n", filename);

    pclass = loadClass(filename);
    if (NULL == pclass) {
        classNotFound(class_name);
    }

    class_info = (CONSTANT_Class_info*)(pclass->constant_pool[pclass->this_class]);
    class_info->pclass = pclass;

    storeLoadedClass(pclass);

    return pclass;
}

Class* systemLoadClass(CONSTANT_Utf8_info* class_utf8_info)
{
    Class* pclass = NULL;
    if (NULL == (pclass = findLoadedClass(class_utf8_info->bytes, class_utf8_info->length))) {
        pclass = loadClassFromDisk(class_utf8_info->bytes);
    }

    return pclass;
}

method_info* findClinitMethod(Class *pclass);
void runClinitMethod(OPENV *env, Class *clinit_class, method_info *method);

Class* loadClassFromDiskRecursive(OPENV* env, const char* class_name)
{
    CONSTANT_Class_info *class_info;
    CONSTANT_Utf8_info *class_utf8_info;
    method_info *method;
    Class *parent_class;
    Class *pclass = NULL;

    char filename[512]; // caution this the class path if too long
    memset(filename, 0, 256);
    strcpy(filename, class_dir);
    strcat(filename, class_name);
    strcat(filename, ".class");

    printf("%s\n", filename);

    pclass = loadClass(filename);
    if (NULL == pclass) {
        classNotFound(class_name);
    }
    class_info = (CONSTANT_Class_info*)(pclass->constant_pool[pclass->this_class]);
    class_info->pclass = pclass;
    if (pclass->super_class > 0) {
        class_info = (CONSTANT_Class_info*)(pclass->constant_pool[pclass->super_class]);
        class_utf8_info = (CONSTANT_Utf8_info*)(pclass->constant_pool[class_info->name_index]);
        if (NULL == (parent_class = findLoadedClass(class_utf8_info->bytes, class_utf8_info->length))) {
            parent_class = loadClassFromDiskRecursive(env, class_utf8_info->bytes);
        }
        class_info->pclass = parent_class;
        pclass->parent_class = parent_class;
    }

    if (NULL != env && NULL != (method = findClinitMethod(pclass))) {
        if (strncmp(class_name, "java", 4) != 0) {
            // only run non jdk's <clinit> method
            runClinitMethod(env, pclass, method);
        }
    }

    storeLoadedClass(pclass);
    return pclass;
}

Class* systemLoadClassRecursive(OPENV* env, CONSTANT_Utf8_info* class_utf8_info)
{
    Class* pclass = NULL;
    if (NULL == (pclass = findLoadedClass(class_utf8_info->bytes, class_utf8_info->length))) {
        pclass = loadClassFromDiskRecursive(env, class_utf8_info->bytes);
    }

    return pclass;
}

int getMethodrefArgsLen(Class* pclass, ushort descriptor_index)
{
    short args_len = 0, args_count=0;
    char c;
    char* args_desc = get_utf8(pclass->constant_pool[descriptor_index]);
    args_desc++;
    while((c = *args_desc) != ')') {
        switch (c) {
            case 'B':
            case 'C':
            case 'F':
            case 'I':
            case 'S':
            case 'Z':
                args_len+=SZ_INT;
                args_count++;
                ++args_desc;
                break;
            case 'D':
            case 'J':
                args_len+=SZ_LONG;
                args_count++;
                ++args_desc;
                break;
            case 'L':
                args_len+=SZ_INT;
                args_desc++;
                while(*args_desc != ';') {
                    args_desc++;
                }
                args_desc++;
                args_count++;
                break;
            case '[':
                args_len+=SZ_INT;
                while(*args_desc == '[') {
                    args_desc++;
                }
                if (*args_desc == 'L') {
                    args_desc++;
                    while(*args_desc != ';') {
                        args_desc++;
                    }
                }
                args_desc++;
                args_count++;
                break;
            default:
                args_desc++;
                break;
        }
    }
    return args_len;
}
