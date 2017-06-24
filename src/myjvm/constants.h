/**
 * +-----------------------------------------------------------------+
 * |  myjvm writing a Java virtual machine step by step (C version)  |
 * +-----------------------------------------------------------------+
 * |  Author: springlchy <sisbeau@126.com>  All Rights Reserved      |
 * +-----------------------------------------------------------------+
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "my_types.h"

#define CONSTANT_Utf8 1
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_Class 7
#define CONSTANT_String 8
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_NameAndType 12
#define CONSTANT_MethodHandle 15
#define CONSTANT_MethodType 16
#define CONSTANT_InvokeDynamic 18

#define ACC_PUBLIC 0x0001
#define ACC_PRIVATE 0x0002
#define ACC_PROTECTED 0x0004
#define ACC_STATIC 0x0008
#define ACC_FINAL 0x0010
#define ACC_SUPER 0x0020
#define ACC_BRIDGE 0x0040
#define ACC_VARARGS 0x0080
#define ACC_NATIVE 0x0100
#define ACC_INTERFACE 0x0200
#define ACC_ABSTRACT 0x0400
#define ACC_STRICT 0x0800
#define ACC_SYNTHETIC 0x1000
#define ACC_ANNOTATION 0x2000
#define ACC_ENUM 0x4000

#define IS_ACC_STATIC(flag) ((flag & ACC_STATIC) == ACC_STATIC)
#define NOT_ACC_STATIC(flag) ((flag & ACC_STATIC) != ACC_STATIC)
#define IS_ACC_NATIVE(flag) ((flag & ACC_NATIVE) == ACC_NATIVE)
#define NOT_ACC_NATIVE(flag) ((flag & ACC_NATIVE) != ACC_NATIVE)

char *cpTypeMap[] = {
    "None", // 0
    "Utf8", //1
    "None", // 2
    "Integer", // 3
    "Float", // 4
    "Long", // 5
    "Double", // 6
    "Class", // 7
    "String", // 8
    "Fieldref", // 9
    "Methodref", // 10
    "InterfaceMethodref", // 11
    "NameAndType", // 12
    "None", // 13
    "None", // 14
    "MethodHandle", // 15
    "MethodType", // 16
    "InvokeDynamic" // 17
};
ushort accFlagInt[] = {
    ACC_PUBLIC,
    ACC_PRIVATE,
    ACC_PROTECTED,
    ACC_STATIC,
    ACC_FINAL,
    ACC_SUPER,
    ACC_BRIDGE,
    ACC_VARARGS,
    ACC_NATIVE,
    ACC_INTERFACE,
    ACC_ABSTRACT,
    ACC_STRICT,
    ACC_SYNTHETIC,
    ACC_ANNOTATION,
    ACC_ENUM
};
char *accFlagMap[] = {
    "ACC_PUBLIC",
    "ACC_PRIVATE",
    "ACC_PROTECTED",
    "ACC_STATIC",
    "ACC_FINAL",
    "ACC_SUPER",
    "ACC_BRIDGE",
    "ACC_VARARGS",
    "ACC_NATIVE",
    "ACC_INTERFACE",
    "ACC_ABSTRACT",
    "ACC_STRICT",
    "ACC_SYNTHETIC",
    "ACC_ANNOTATION",
    "ACC_ENUM"
};

char* formatAccessFlag(ushort accFlag)
{
    char *accFlagStr = (char*)malloc(sizeof(char)*255);
    int i;
    int len = sizeof(accFlagInt)/sizeof(short int);
    memset(accFlagStr, 0, 255);

    for(i=0; i<len; i++) {
        if ((accFlag & accFlagInt[i]) == accFlagInt[i]) {
            strcat(accFlagStr, accFlagMap[i]);
            strcat(accFlagStr, " ");
        }
    }

    return accFlagStr;
}

#endif // CONSTANTS_H
