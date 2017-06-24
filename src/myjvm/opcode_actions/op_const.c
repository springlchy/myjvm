/**
 * +-----------------------------------------------------------------+
 * |  myjvm writing a Java virtual machine step by step (C version)  |
 * +-----------------------------------------------------------------+
 * |  Author: springlchy <sisbeau@126.com>  All Rights Reserved      |
 * +-----------------------------------------------------------------+
 */

#ifndef OP_CONST_C
#define OP_CONST_C

#include "opcode.h"
#include "op_core.h"

Opreturn do_nop(OPENV *env)
{
    RETURNV;
}
Opreturn do_aconst_nul(OPENV *env)
{
    PUSH_STACKR(env->current_stack, NULL, Reference);
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_r);
    RETURNV;
}
Opreturn do_iconst_m1(OPENV *env)
{
    PUSH_STACK(env->current_stack, -1, int);
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_i);
    RETURNV;
}
Opreturn do_iconst_0(OPENV *env)
{
    PUSH_STACK(env->current_stack, 0, int);
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_i);
    RETURNV;
}
Opreturn do_iconst_1(OPENV *env)
{
    PUSH_STACK(env->current_stack, 1, int);
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_i);
    RETURNV;
}
Opreturn do_iconst_2(OPENV *env)
{
    PUSH_STACK(env->current_stack, 2, int);
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_i);
    RETURNV;
}
Opreturn do_iconst_3(OPENV *env)
{
    PUSH_STACK(env->current_stack, 3, int);
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_i);
    RETURNV;
}
Opreturn do_iconst_4(OPENV *env)
{
    PUSH_STACK(env->current_stack, 4, int);
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_i);
    RETURNV;
}
Opreturn do_iconst_5(OPENV *env)
{
    PUSH_STACK(env->current_stack, 5, int);
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_i);
    RETURNV;
}
Opreturn do_lconst_0(OPENV *env)
{
    PUSH_STACKL(env->current_stack, 0, long);
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_l);
    RETURNV;
}
Opreturn do_lconst_1(OPENV *env)
{
    PUSH_STACKL(env->current_stack, 1, long);
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_l);
    RETURNV;
}
Opreturn do_fconst_0(OPENV *env)
{
    PUSH_STACK(env->current_stack, 0.0f, float);
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_f);
    RETURNV;
}
Opreturn do_fconst_1(OPENV *env)
{
    PUSH_STACK(env->current_stack, 1.0f, float);
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_f);
    RETURNV;
}
Opreturn do_fconst_2(OPENV *env)
{
    PUSH_STACK(env->current_stack, 2.0f, float);
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_f);
    RETURNV;
}
Opreturn do_dconst_0(OPENV *env)
{
    PUSH_STACKL(env->current_stack, 0.0, double);

    RETURNV;
}
Opreturn do_dconst_1(OPENV *env)
{
    PUSH_STACKL(env->current_stack, 1.0, double);
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_d);
    RETURNV;
}
Opreturn do_bipush(OPENV *env)
{
    PRINTD(TO_BYTE(env->pc));
    PUSH_STACK(env->current_stack,TO_BYTE(env->pc), int);
    INC_PC(env->pc);
    printCurrentEnv(env, "bipush");
    //DEBUG_SET_SP_TYPE(env->dbg, debug_type_c);
    RETURNV;
}
Opreturn do_sipush(OPENV *env)
{
    PRINTD(TO_SHORT(env->pc));
    PUSH_STACK(env->current_stack,TO_SHORT(env->pc), int);
    debug("sipush=%d, %d", TO_SHORT(env->pc), PICK_STACK(env->current_stack, short));
    INC2_PC(env->pc);
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_s);
    RETURNV;
}
Opreturn do_ldc(OPENV *env)
{
    FILE *fp;
    int i;
    CArray_char* char_arr;
    Object *str_obj;
    PRINTSD(TO_CHAR(env->pc));
    ushort index = (ushort)(TO_CHAR(env->pc));
    uchar tag;
    tag = *(char*)(env->current_class->constant_pool[index]);

    INC_PC(env->pc);
    switch (tag) {
    case CONSTANT_Integer:
        PUSH_STACK(env->current_stack, ((CONSTANT_Integer_info*)(env->current_class->constant_pool[index]))->value, int);
        DEBUG_SET_SP_TYPE(env->dbg, debug_type_i);
        break;
    case CONSTANT_Float:
        PUSH_STACK(env->current_stack, ((CONSTANT_Float_info*)(env->current_class->constant_pool[index]))->value, float);
        DEBUG_SET_SP_TYPE(env->dbg, debug_type_f);
        break;
    case CONSTANT_String:
        debug("this class = %s", get_this_class_name(env->current_class));
        debug("ldc error: tag=%d, index=%d", tag, index);
        printf("ldc: stack=%p, sp=%p, pc=%p\n", env->current_stack, env->current_stack->sp, env->pc);

        // begin save to log
        printCurrentEnv(env, "ldc");
        // end save to log

        char_arr = newCArray_char_fromConstStr(env->current_class, index);
        str_obj = newConstString(env, char_arr);
        //PUSH_STACKR(env->current_stack, str_obj, Reference);
        printf("create const string success\n");
        printf("ldcend: stack=%p, sp=%p, pc=%p\n", env->current_stack, env->current_stack->sp, env->pc);
        // begin save to log
        printCurrentEnv(env, "ldc end");
        // end save to log
        //exit(1);
        break;
    default:
        debug("ldc error: tag=%d, index=%d", tag, index);
        exit(1);
    }

    RETURNV;
}
Opreturn do_ldc_w(OPENV *env)
{
    PRINTSD(TO_SHORT(env->pc));
    ushort index = (ushort)(TO_SHORT(env->pc));
    uchar tag;
    tag = *(char*)(env->current_class->constant_pool[index]);
    if (tag == CONSTANT_Integer) {
        PUSH_STACK(env->current_stack, ((CONSTANT_Integer_info*)(env->current_class->constant_pool[index]))->value, int);
        DEBUG_SET_SP_TYPE(env->dbg, debug_type_i);
    } else if (tag == CONSTANT_Float) {
        PUSH_STACK(env->current_stack, ((CONSTANT_Float_info*)(env->current_class->constant_pool[index]))->value, float);
        DEBUG_SET_SP_TYPE(env->dbg, debug_type_f);
    } else {
        debug("ldc_w error: tag=%d, index=%d", tag, index);
        exit(1);
    }
    INC2_PC(env->pc);
    RETURNV;
}
Opreturn do_ldc2_w(OPENV *env)
{
    PRINTSD(TO_SHORT(env->pc));
    ushort index = (ushort)(TO_SHORT(env->pc));
    uchar tag;
    tag = *(char*)(env->current_class->constant_pool[index]);
    if (tag == CONSTANT_Long) {
        PUSH_STACKL(env->current_stack, ((CONSTANT_Long_info*)(env->current_class->constant_pool[index]))->value, long);
        DEBUG_SET_SP_TYPE(env->dbg, debug_type_l);
    } else if (tag == CONSTANT_Double) {
        PUSH_STACKL(env->current_stack, ((CONSTANT_Double_info*)(env->current_class->constant_pool[index]))->value, double);
        DEBUG_SET_SP_TYPE(env->dbg, debug_type_d);
    } else {
        debug("ldc2_w error: tag=%d, index=%d", tag, index);
        exit(1);
    }

    INC2_PC(env->pc);
    RETURNV;
}
#endif
