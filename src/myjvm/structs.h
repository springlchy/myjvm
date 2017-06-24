#ifndef STRUCTS_H
#define STRUCTS_H

#include "constants.h"

typedef struct _CONSTANT_Utf8_info {
    uchar tag;
    ushort length;
    char *bytes;
} CONSTANT_Utf8_info;

typedef struct _CONSTANT_String_info {
    uchar tag;
    ushort string_index;
} CONSTANT_String_info;
typedef struct _CONSTANT_Integer_info {
    uchar tag;
    int value;
} CONSTANT_Integer_info;
typedef struct _CONSTANT_Float_info {
    uchar tag;
    float value;
} CONSTANT_Float_info;

typedef struct _CONSTANT_Long_info {
    uchar tag;
    long value;
} CONSTANT_Long_info;
typedef struct _CONSTANT_Double_info {
    uchar tag;
    double value;
} CONSTANT_Double_info;

typedef struct _CONSTANT_NameAndType_info {
    uchar tag;
    ushort name_index;
    ushort descriptor_index;
} CONSTANT_NameAndType_info;
typedef struct _CONSTANT_MethodHandle_info {
    uchar tag;
    uchar reference_kind;
    ushort reference_index;
} CONSTANT_MethodHandle_info;
typedef struct _CONSTANT_MethodType_info {
    uchar tag;
    ushort descriptor_index;
} CONSTANT_MethodType_info;
typedef struct _CONSTANT_InvokeDynamic_info {
    uchar tag;
    ushort bootstrap_method_attr_index;
    ushort name_and_type_index;
} CONSTANT_InvokeDynamic_info;

typedef void** cp_info;

typedef struct _attribute_info{
    ushort attribute_name_index;
    uint attribute_length;
    uchar *info;
} attribute_info;

typedef struct _field_info{
    ushort access_flags;
    ushort name_index;
    ushort descriptor_index;
    ushort attributes_count;
    attribute_info **attributes;
    ushort findex; // field index, [for fieldref]
    uchar ftype; // field type [for fieldref]
} field_info;

typedef struct _exception_table {
    ushort start_pc;
    ushort end_pc;
    ushort handler_pc;
    ushort catch_type;
} exception_table;
typedef struct _Code_attribute {
    ushort attribute_type;
    ushort max_stack;
    ushort max_locals;
    uint code_length;
    uchar *code;
    ushort exception_table_length;
    exception_table *exceptions;
    ushort attributes_count;
    attribute_info **attributes;
} Code_attribute;

typedef struct _method_info{
    ushort access_flags;
    ushort name_index;
    ushort descriptor_index;
    ushort attributes_count;
    attribute_info **attributes;
    Code_attribute* code_attribute_addr; // address of code attribute
    ushort args_len;
} method_info;

typedef struct _ClassFile{
    uint magic;
    ushort minor_version;
    ushort major_version;
    ushort constant_pool_count;
    cp_info constant_pool;
    ushort access_flags;
    ushort this_class;
    ushort super_class;
    ushort interface_count;
    ushort *interfaces;
    ushort fields_count;
    field_info **fields;
    ushort methods_count;
    method_info **methods;
    ushort attributes_count;
    attribute_info **attributes;
    struct _ClassFile *parent_class;
    int parent_fields_size;
    int fields_size;
    ushort static_field_size;
    char *static_fields;
    char clinit_runned;
} ClassFile;

typedef ClassFile Class;

#include "method_table.h"

typedef struct _CONSTANT_Fieldref_info {
    uchar tag;
    ushort class_index;
    ushort name_and_type_index;
    ushort findex; // field index, [for fieldref]
    uchar ftype; // field type [for fieldref]
} CONSTANT_Fieldref_info;

typedef struct _CONSTANT_Methodref_info {
    uchar tag;
    ushort class_index;
    ushort name_and_type_index;
    void* ref_addr; //real address, [for methodref]
    ushort args_len;
    Class *pclass;
    MethodTable *mtable;
} CONSTANT_Methodref_info;

typedef CONSTANT_Methodref_info CONSTANT_InterfaceMethodref_info;

typedef struct _CONSTANT_Class_info {
    uchar tag;
    ushort name_index;
    Class* pclass;
} CONSTANT_Class_info;

typedef struct _line_number_table {
    ushort start_pc;
    ushort line_number;
} line_number_table;

typedef struct _LineNumberTable_attribute {
    ushort attribute_type;
    uint attribute_length;
    ushort table_length;
    line_number_table *tables;
} LineNumberTable_attribute;

typedef struct _local_variable_table {
    ushort start_pc;
    ushort length;
    ushort name_index;
    ushort descriptor_index;
    ushort index;
} local_variable_table;
typedef struct _LocalVariableTable_attribute {
    ushort attribute_type;
    uint attribute_length;
    ushort table_length;
    local_variable_table *tables;
}  LocalVariableTable_attribute;

typedef struct _local_variable_type_table {
    ushort start_pc;
    ushort length;
    ushort name_index;
    ushort signature_index;
    ushort index;
} local_variable_type_table;
typedef struct _LocalVariableTypeTable_attribute {
    ushort attribute_type;
    uint attribute_length;
    ushort table_length;
    local_variable_type_table *tables;
} LocalVariableTypeTable_attribute;


#endif
