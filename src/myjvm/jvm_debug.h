/**
 * +-----------------------------------------------------------------+
 * |  myjvm writing a Java virtual machine step by step (C version)  |
 * +-----------------------------------------------------------------+
 * |  Author: springlchy <sisbeau@126.com>  All Rights Reserved      |
 * +-----------------------------------------------------------------+
 */

#ifndef JVM_DEBUG_H
#define JVM_DEBUG_H

#include "constants.h"

#define debug_type_c 0x01
#define debug_type_s 0x02
#define debug_type_i 0x03
#define debug_type_f 0x04
#define debug_type_l 0x05
#define debug_type_d 0x06
#define debug_type_a 0x07
#define debug_type_r 0x08

#ifdef DEBUG

#define DEBUG_SET_LV_TYPE(dbg, vindex, dtype) *(dbg->localvar_type+vindex)=dtype
#define DEBUG_SET_SP_TYPE(dbg, dtype) *(dbg->spvar_type)=dtype;dbg->spvar_type+=1;
#define DEBUG_CAST_SP_TYPE(dbg, dtype) *(dbg->spvar_type)=dtype

#define DEBUG_SP_UP(dbg) dbg->spvar_type+=1
#define DEBUG_SP_DOWN(dbg) dbg->spvar_type-=1
#define DEBUG_SP_UPL(dbg) dbg->spvar_type+=2
#define DEBUG_SP_DOWNL(dbg) dbg->spvar_type-=2
#define DEBUG_SP_UPT(dbg) dbg->spvar_type+=3
#define DEBUG_SP_DOWNT(dbg) dbg->spvar_type-=3

#else

#define SET_DEBUG_LV_TYPE(dbg, vindex, dtype)
#define SET_DEBUG_SP_TYPE(dbg, dtype)
#define DEBUG_SP_UP(dbg)
#define DEBUG_SP_DOWN(dbg)
#define DEBUG_SP_UPL(dbg)
#define DEBUG_SP_DOWNL(dbg)
#define DEBUG_SP_UPT(dbg)
#define DEBUG_SP_DOWNT(dbg)

#endif

#define debug(format,...) printf("\nDEBUG:");\
    printf(format, __VA_ARGS__ );\
    printf("\n")

typedef struct _DebugType {
    char* localvar_type;
    char* localvar_base;
    char* spvar_type;
    char* spvar_base;
} DebugType;

DebugType* newDebugType(ushort local_vars, int stack_size)
{
    DebugType* dbg = (DebugType*)malloc(sizeof(DebugType) + (local_vars+1) + stack_size);
    memset(dbg, 0, sizeof(DebugType) + (local_vars+1) + stack_size);

    dbg->localvar_type = (char*)(dbg+1);
    dbg->localvar_base = dbg->localvar_type;
    dbg->spvar_type = dbg->localvar_type + local_vars+1;
    dbg->spvar_base = dbg->spvar_type;
    return dbg;
}

#endif // JVM_DEBUG_H
