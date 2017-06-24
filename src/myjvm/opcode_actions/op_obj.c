/**
 * +-----------------------------------------------------------------+
 * |  myjvm writing a Java virtual machine step by step (C version)  |
 * +-----------------------------------------------------------------+
 * |  Author: springlchy <sisbeau@126.com>  All Rights Reserved      |
 * +-----------------------------------------------------------------+
 */

#ifndef OP_OBJ_C
#define OP_OBJ_C

#include "opcode.h"
#include "op_core.h"

extern void callThisClassMethod(OPENV *env, ushort mindex);
extern Class* findLoadedClass(const char* class_name, int name_len);
extern void callOtherClassMethod(OPENV *env, CONSTANT_Methodref_info* method_ref);
extern Class* systemLoadClass(CONSTANT_Utf8_info* class_utf8_info);
extern Class* systemLoadClassRecursive(OPENV *env, CONSTANT_Utf8_info* class_utf8_info);
extern void resolveClassInstanceField(Class* caller_class, CONSTANT_Fieldref_info **pfield_ref);
extern void resolveClassMethod(Class* caller_class, CONSTANT_Methodref_info **pmethod_ref);
extern void resolveClassSpecialMethod(Class* caller_class, CONSTANT_Methodref_info **pmethod_ref);
extern void callClassSpecialMethod(OPENV *env, int mindex);

Opreturn do_getstatic(OPENV *env)
{
    ArrayRef arr_ref;
    CONSTANT_Fieldref_info *fieldref;
    Class *pclass;
    cp_info cp;
    short index = TO_SHORT(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    cp = env->current_class->constant_pool;
    fieldref = (CONSTANT_Fieldref_info*)(cp[index]);

    if (0 == fieldref->ftype) {
        // TODO: resolve this fields
        resolveClassStaticField(env->current_class, &fieldref);
    }

    pclass = ((CONSTANT_Class_info*)(cp[fieldref->class_index]))->pclass;

    switch (fieldref->ftype) {
        case 'B': // byte
            OP_GET_STATIC_FIELDI(pclass, fieldref->findex, byte);
            break;
        case 'C': // char
            OP_GET_STATIC_FIELDI(pclass, fieldref->findex, char);
            break;
        case 'S': // short
            OP_GET_STATIC_FIELDI(pclass, fieldref->findex, short);
            break;
        case 'Z': // boolean
            OP_GET_STATIC_FIELDI(pclass, fieldref->findex, int);
            break;
        case 'I': // integer
            OP_GET_STATIC_FIELDI(pclass, fieldref->findex, int);
            break;
        case 'F': // float
            OP_GET_STATIC_FIELDF(pclass, fieldref->findex, float);
            break;
        case '[': // reference
            arr_ref = *(ArrayRef*)(pclass->static_fields+(fieldref->findex<<2));
            displayStaticFields(pclass);
            OP_GET_STATIC_FIELDR(pclass, fieldref->findex, ArrayRef);
            break;
        case 'L': // reference
            OP_GET_STATIC_FIELDR(pclass, fieldref->findex, Reference);
             break;
        case 'J': // long
            OP_GET_STATIC_FIELDL(pclass, fieldref->findex, long);
            break;
        case 'D': // double
            OP_GET_STATIC_FIELDL(pclass, fieldref->findex, double);
            break;
        default:
            printf("Error: getfield, ftype=%d\n", fieldref->ftype);
            exit(1);
            break;
    }

    INC2_PC(env->pc);
}

Opreturn do_putstatic(OPENV *env)
{
    ArrayRef arr_ref;
    CONSTANT_Fieldref_info *fieldref;
    Class *pclass;
    cp_info cp;
    short index = TO_SHORT(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    cp = env->current_class->constant_pool;
    fieldref = (CONSTANT_Fieldref_info*)(cp[index]);


    if (0 == fieldref->ftype) {
        // TODO: resolve this fields
        resolveClassStaticField(env->current_class, &fieldref);
    }

    pclass = ((CONSTANT_Class_info*)(cp[fieldref->class_index]))->pclass;
    switch (fieldref->ftype) {
        case 'B': // byte
            OP_PUT_STATIC_FIELDI(pclass, fieldref->findex, byte);
            debug("static field: findex=%d, value=%d", fieldref->findex, GET_STATIC_FIELD(pclass, fieldref->findex, byte));
            break;
        case 'C': // char
            OP_PUT_STATIC_FIELDI(pclass, fieldref->findex, char);
            debug("static field: findex=%d, value=%d", fieldref->findex, GET_STATIC_FIELD(pclass, fieldref->findex, char));
            break;
        case 'S': // short
            OP_PUT_STATIC_FIELDI(pclass, fieldref->findex, short);
            debug("static field: findex=%d, value=%d", fieldref->findex, GET_STATIC_FIELD(pclass, fieldref->findex, short));
            break;
        case 'Z': // boolean
            OP_PUT_STATIC_FIELDI(pclass, fieldref->findex, int);
            debug("static field: findex=%d, value=%d", fieldref->findex, GET_STATIC_FIELD(pclass, fieldref->findex, int));
            break;
        case 'I': // integer
            OP_PUT_STATIC_FIELDI(pclass, fieldref->findex, int);
            debug("static field: findex=%d, value=%d", fieldref->findex, GET_STATIC_FIELD(pclass, fieldref->findex, int));
            break;
        case 'F': // float
            OP_PUT_STATIC_FIELDF(pclass, fieldref->findex, float);
            debug("static field: findex=%d, value=%f", fieldref->findex, GET_STATIC_FIELD(pclass, fieldref->findex, float));
            break;
        case '[': // reference
            OP_PUT_STATIC_FIELDR(pclass, fieldref->findex, ArrayRef);
            displayStaticFields(pclass);
            printf("###################put static#######################\n");
            //system("pause");
            break;
        case 'L': // reference
            OP_PUT_STATIC_FIELDR(pclass, fieldref->findex, Reference);
            break;
        case 'J': // long
            OP_PUT_STATIC_FIELDL(pclass, fieldref->findex, long);
            debug("static field: findex=%d, value=%ld", fieldref->findex, GET_STATIC_FIELD(pclass, fieldref->findex, long));
            break;
        case 'D': // double
            OP_PUT_STATIC_FIELDL(pclass, fieldref->findex, double);
            debug("static field: findex=%d, value=%lf", fieldref->findex, GET_STATIC_FIELD(pclass, fieldref->findex, double));
            break;
        default:
            printf("Error: getfield, ftype=%d\n", fieldref->ftype);
            exit(1);
            break;
    }

    INC2_PC(env->pc);
}
Opreturn do_getfield(OPENV *env)
{
    CONSTANT_Fieldref_info *fieldref;
    cp_info cp;
    Object *obj;
    short index = TO_SHORT(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    cp = env->current_class->constant_pool;
    fieldref = (CONSTANT_Fieldref_info*)(cp[index]);

    GET_STACKR(env->current_stack, obj, Reference);
    if (0 == fieldref->ftype) {
        // TODO: resolve this field
        resolveClassInstanceField(env->current_class, &fieldref);
    }

    switch (fieldref->ftype) {
        case 'B': // byte
            OP_GET_FIELDI(obj, fieldref->findex, byte);
            debug("get-field:findex=%d, value=%d, stackvalue=%d", fieldref->findex, GET_FIELD(obj, fieldref->findex, byte), PICK_STACK(env->current_stack, byte));
            break;
        case 'C': // char
            OP_GET_FIELDI(obj, fieldref->findex, char);
            debug("get-field:findex=%d, value=%d, stackvalue=%d", fieldref->findex, GET_FIELD(obj, fieldref->findex, char), PICK_STACK(env->current_stack, char));
            break;
        case 'S': // short
            OP_GET_FIELDI(obj, fieldref->findex, short);
            debug("get-field:findex=%d, value=%d, stackvalue=%d", fieldref->findex, GET_FIELD(obj, fieldref->findex, short), PICK_STACK(env->current_stack, short));
            break;
        case 'Z': // boolean
            OP_GET_FIELDI(obj, fieldref->findex, char);
            debug("get-field:findex=%d, value=%d, stackvalue=%d", fieldref->findex, GET_FIELD(obj, fieldref->findex, char), PICK_STACK(env->current_stack, char));
            break;
        case 'I': // integer
            debug("findex=%d, field=%d", fieldref->findex, GET_FIELD(obj, fieldref->findex, int));
            OP_GET_FIELDI(obj, fieldref->findex, int);
            debug("get-field:findex=%d, value=%d, stackvalue=%d", fieldref->findex, GET_FIELD(obj, fieldref->findex, int), PICK_STACK(env->current_stack, int));
            break;
        case 'F': // float
            OP_GET_FIELDI(obj, fieldref->findex, float);
            debug("get-field:value=%f, stackvalue=%f", GET_FIELD(obj, fieldref->findex, float), PICK_STACK(env->current_stack, float));
            break;
        case '[': // reference
        case 'L': // reference
            OP_GET_FIELDR(obj, fieldref->findex, Reference);
            debug("get-field:value=%p, stackvalue=%p", GET_FIELD(obj, fieldref->findex, Reference), PICK_STACK(env->current_stack, Reference));
            break;
        case 'J': // long
            OP_GET_FIELDL(obj, fieldref->findex, long);
            debug("get-field:value=%ld, stackvalue=%ld", GET_FIELD(obj, fieldref->findex, long), PICK_STACK(env->current_stack, long));
            break;
        case 'D': // double
            OP_GET_FIELDL(obj, fieldref->findex, double);
            debug("get-field:value=%lf, stackvalue=%lf", GET_FIELD(obj, fieldref->findex, double),PICK_STACK(env->current_stack, double));
            break;
        default:
            printf("Error: getfield, ftype=%d\n", fieldref->ftype);
            exit(1);
            break;
    }

    INC2_PC(env->pc);
}
Opreturn do_putfield(OPENV *env)
{
    CONSTANT_Fieldref_info *fieldref;
    CONSTANT_Class_info* class_info;
    cp_info cp;
    Object *obj;
    short index = TO_SHORT(env->pc);

    PRINTSD(TO_SHORT(env->pc));

    cp = env->current_class->constant_pool;
    fieldref = (CONSTANT_Fieldref_info*)(cp[index]);
    class_info = (CONSTANT_Class_info*)(cp[fieldref->class_index]);

    if (0 == fieldref->ftype) {
        // TODO: resolve this field
        resolveClassInstanceField(env->current_class, &fieldref);
    }

    switch (fieldref->ftype) {
        case 'B': // byte
            OP_PUT_FIELDI(obj, fieldref->findex, byte);
            break;
        case 'C': // char
            OP_PUT_FIELDI(obj, fieldref->findex, char);
            break;
        case 'S': // short
            OP_PUT_FIELDI(obj, fieldref->findex, short);
            break;
        case 'Z': // boolean
            OP_PUT_FIELDI(obj, fieldref->findex, char);
            break;
        case 'I': // integer
            OP_PUT_FIELDI(obj, fieldref->findex, int);
            debug("findex=%d, field=%d", fieldref->findex, GET_FIELD(obj, fieldref->findex, int));
            break;
        case 'F': // float
            OP_PUT_FIELDF(obj, fieldref->findex, float);
            debug("findex=%d, field=%d", fieldref->findex, GET_FIELD(obj, fieldref->findex, float));
            break;
        case '[': // reference
        case 'L': // reference
            OP_PUT_FIELDR(obj, fieldref->findex, Reference);
            break;
        case 'J': // long
            OP_PUT_FIELDL(obj, fieldref->findex, long);
            break;
        case 'D': // double
            OP_PUT_FIELDL(obj, fieldref->findex, double);
            break;
        default:
            printf("\nError: getfield, ftype=%d\n", fieldref->ftype);
            exit(1);
            break;
    }
    INC2_PC(env->pc);
}
Opreturn do_invokevirtual(OPENV *env)
{
    PRINTSD(TO_SHORT(env->pc));
    short mindex = TO_SHORT(env->pc);
    INC2_PC(env->pc);

    callClassVirtualMethod(env, mindex);
}
Opreturn do_invokespecial(OPENV *env)
{
    PRINTSD(TO_SHORT(env->pc));
    short mindex = TO_SHORT(env->pc);
    INC2_PC(env->pc);

    callClassSpecialMethod(env, mindex);
}
Opreturn do_invokestatic(OPENV *env)
{
    PRINTSD(TO_SHORT(env->pc));
    short mindex = TO_SHORT(env->pc);
    INC2_PC(env->pc);
    callStaticClassMethod(env, mindex);
}
Opreturn do_invokeinterface(OPENV *env)
{
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn do_invokedynamic(OPENV *env)
{
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn do_new(OPENV *env)
{
    Class* pclass;
    CONSTANT_Utf8_info* utf8_info;
    CONSTANT_Class_info* class_info;
    PRINTSD(TO_SHORT(env->pc));
    short index = TO_SHORT(env->pc);
    Object *obj;
    INC2_PC(env->pc);

    if (env->current_class->this_class == index) {
        pclass = env->current_class;
    } else {
        // create other class
        class_info = (CONSTANT_Class_info*)(env->current_class->constant_pool[index]);
        utf8_info = (CONSTANT_Utf8_info*)(env->current_class->constant_pool[class_info->name_index]);
        printf("class = %s\n", utf8_info->bytes);
        utf8_info = (CONSTANT_Utf8_info*)(env->current_class->constant_pool[env->current_stack->method->name_index]);
        printf("method = %s\n", utf8_info->bytes);

        if (class_info->pclass == NULL) {
            debug("load pclass: %d", 2);
            utf8_info = (CONSTANT_Utf8_info*)(env->current_class->constant_pool[class_info->name_index]);
            pclass = class_info->pclass = findLoadedClass(utf8_info->bytes, utf8_info->length);
            debug("findLoadedClass pclass=%p", pclass);
        } else {
            pclass = class_info->pclass;
        }

        if (NULL == pclass) {
            pclass = class_info->pclass = systemLoadClassRecursive(env, utf8_info);
            debug("systemLoadClassRecursive pclass=%p", pclass);
        }
    }

    debug("goto new Object: class_index=%d, %p", pclass->this_class, pclass);
    printCurrentEnv(env, "after new:");
    obj = newObject(env, pclass);
    printCurrentEnv(env, "before new:");
    env->current_obj = obj;
    debug("new: obj=%p,pc=%p,sp=%p\n", obj, env->pc,env->current_stack->sp);
    PUSH_STACKR(env->current_stack, obj, Reference);
    printCurrentEnv(env, "afrer push obj:");
}

Opreturn do_newarray(OPENV *env)
{
    int arr_count;
    char arr_type;
    PRINTSD(TO_CHAR(env->pc));
    arr_type = TO_CHAR(env->pc);
    GET_STACK(env->current_stack, arr_count, int);
    char *sp_old = env->current_stack->sp;
    PUSH_STACKR(env->current_stack, generalNewArray(arr_type, arr_count), ArrayRef);

    INC_PC(env->pc);
}
Opreturn do_anewarray(OPENV *env)
{
    int arr_count;
    int arr_type_index = TO_SHORT(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    GET_STACK(env->current_stack, arr_count, int);
    PUSH_STACK(env->current_stack, newCArray_Reference(arr_type_index&0x10, arr_count, 1), ArrayRef);

    INC2_PC(env->pc);
}
Opreturn do_arraylength(OPENV *env)
{
    OP_ARRAY_LENGTH(env);

    RETURNV;
}
Opreturn do_athrow(OPENV *env)
{
    printf("[athrow] not implemented yet\n");
    exit(1);
    RETURNV;
}
Opreturn do_checkcast(OPENV *env)
{
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn do_instanceof(OPENV *env)
{
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn do_monitorenter(OPENV *env)
{
    printf("[monitorenter] not implemented yet\n");
    exit(1);
    RETURNV;
}
Opreturn do_monitorexit(OPENV *env)
{
    printf("[monitorexit] not implemented yet\n");
    exit(1);
    RETURNV;
}

#endif
