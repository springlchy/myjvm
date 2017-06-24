/**
 * +-----------------------------------------------------------------+
 * |  myjvm writing a Java virtual machine step by step (C version)  |
 * +-----------------------------------------------------------------+
 * |  Author: springlchy <sisbeau@126.com>  All Rights Reserved      |
 * +-----------------------------------------------------------------+
 */

#ifndef OP_STACK_C
#define OP_STACK_C

#include "opcode.h"
#include "op_core.h"

Opreturn do_pop(OPENV *env)
{
    POP_STACK(env->current_stack);
    DEBUG_SP_DOWN(env->dbg);
    RETURNV;
}
Opreturn do_pop2(OPENV *env)
{
    POP_STACKL(env->current_stack);
    DEBUG_SP_DOWNL(env->dbg);
    RETURNV;
}
Opreturn do_dup(OPENV *env)
{
    char *csp = SP_DOWN_POS(env->current_stack);
    memcpy(env->current_stack->sp, csp, SZ_INT);
    SP_UP(env->current_stack);

    DEBUG_SP_UP(env->dbg);
    RETURNV;
}
Opreturn do_dup_x1(OPENV *env)
{
    uchar *csp = SP_DOWN_POSL(env->current_stack);
    memmove(SP_DOWN_POS(env->current_stack), csp, SZ_LONG);
    memmove(csp, env->current_stack->sp, SZ_INT);
    SP_UP(env->current_stack);

    DEBUG_SP_UP(env->dbg);
    RETURNV;
}
Opreturn do_dup_x2(OPENV *env)
{
    int offset = SZ_INT + SZ_LONG;
    uchar *csp = env->current_stack->sp - offset;
    memmove(csp, SP_DOWN_POSL(env->current_stack), offset);
    memmove(env->current_stack->sp, csp, SZ_INT);
    SP_UP(env->current_stack);

    DEBUG_SP_UP(env->dbg);
    RETURNV;
}
Opreturn do_dup2(OPENV *env)
{
    uchar *csp = SP_DOWN_POSL(env->current_stack);
    memcpy(env->current_stack->sp, csp, SZ_LONG);
    SP_UPL(env->current_stack);

    DEBUG_SP_UPL(env->dbg);
    RETURNV;
}
Opreturn do_dup2_x1(OPENV *env)
{
    uchar *csp = SP_DOWN_POSL(env->current_stack);
    uchar *csp2 = csp - SZ_INT;
    memcpy(env->current_stack->sp, csp, SZ_LONG);
    memcpy(SP_DOWN_POS(env->current_stack), csp2, SZ_INT);
    memcpy(csp2, env->current_stack->sp,SZ_LONG);
    SP_UPL(env->current_stack);

    DEBUG_SP_UPL(env->dbg);
    RETURNV;
}
Opreturn do_dup2_x2(OPENV *env)
{
    uchar *csp = SP_DOWN_POSL(env->current_stack);
    uchar *csp2 = csp - SZ_LONG;
    memcpy(env->current_stack->sp, csp, SZ_LONG);
    memcpy(csp, csp2, SZ_LONG);
    memcpy(csp2, env->current_stack->sp, SZ_LONG);

    SP_UPL(env->current_stack);

    DEBUG_SP_UPL(env->dbg);
    RETURNV;
}
Opreturn do_swap(OPENV *env)
{
    uchar c_tmp[4];
    uchar *csp = SP_DOWN_POS(env->current_stack);
    memcpy(csp, c_tmp, SZ_INT);
    memcpy(SP_DOWN_POSL(env->current_stack), csp, SZ_INT);
    memcpy(c_tmp, csp, SZ_INT);
    RETURNV;
}

#endif
