/**
 * +-----------------------------------------------------------------+
 * |  myjvm writing a Java virtual machine step by step (C version)  |
 * +-----------------------------------------------------------------+
 * |  Author: springlchy <sisbeau@126.com>  All Rights Reserved      |
 * +-----------------------------------------------------------------+
 */

#ifndef OP_STORE_C
#define OP_STORE_C

#include "opcode.h"
#include "op_core.h"

Opreturn do_istore(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    int i = (int)(TO_CHAR(env->pc));
    ISTORE(env, i);
    INC_PC(env->pc);
    RETURNV;
}
Opreturn do_lstore(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    int i = (int)(TO_CHAR(env->pc));
    LSTORE(env, i);
    INC_PC(env->pc);
    RETURNV;
}
Opreturn do_fstore(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    int i = (int)(TO_CHAR(env->pc));
    FSTORE(env, i);
    INC_PC(env->pc);
    RETURNV;
}
Opreturn do_dstore(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    int i = (int)(TO_CHAR(env->pc));
    DSTORE(env, i);
    INC_PC(env->pc);
    RETURNV;
}
Opreturn do_astore(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    int i = (int)(TO_CHAR(env->pc));
    ASTORE(env, i);
    INC_PC(env->pc);
    RETURNV;
}
Opreturn do_istore_0(OPENV *env)
{
    ISTORE(env, 0);
    RETURNV;
}
Opreturn do_istore_1(OPENV *env)
{
    ISTORE(env, 1);
    RETURNV;
}
Opreturn do_istore_2(OPENV *env)
{
    ISTORE(env, 2);
    RETURNV;
}
Opreturn do_istore_3(OPENV *env)
{
    ISTORE(env, 3);
    RETURNV;
}
Opreturn do_lstore_0(OPENV *env)
{
    LSTORE(env, 0);
    RETURNV;
}
Opreturn do_lstore_1(OPENV *env)
{
    LSTORE(env, 1);
    RETURNV;
}
Opreturn do_lstore_2(OPENV *env)
{
    LSTORE(env, 2);
    RETURNV;
}
Opreturn do_lstore_3(OPENV *env)
{
    LSTORE(env, 3);
    RETURNV;
}
Opreturn do_fstore_0(OPENV *env)
{
    FSTORE(env, 0);
    RETURNV;
}
Opreturn do_fstore_1(OPENV *env)
{
    FSTORE(env, 1);
    RETURNV;
}
Opreturn do_fstore_2(OPENV *env)
{
    FSTORE(env, 2);
    RETURNV;
}
Opreturn do_fstore_3(OPENV *env)
{
    FSTORE(env, 3);
    RETURNV;
}
Opreturn do_dstore_0(OPENV *env)
{
    DSTORE(env, 0);
    RETURNV;
}
Opreturn do_dstore_1(OPENV *env)
{
    DSTORE(env, 1);
    RETURNV;
}
Opreturn do_dstore_2(OPENV *env)
{
    DSTORE(env, 2);
    RETURNV;
}
Opreturn do_dstore_3(OPENV *env)
{
    DSTORE(env, 3);
    RETURNV;
}
Opreturn do_astore_0(OPENV *env)
{
    ASTORE(env, 0);
    RETURNV;
}
Opreturn do_astore_1(OPENV *env)
{
    ASTORE(env, 1);
    RETURNV;
}
Opreturn do_astore_2(OPENV *env)
{
    ASTORE(env, 2);
    RETURNV;
}
Opreturn do_astore_3(OPENV *env)
{
    ASTORE(env, 3);
    RETURNV;
}
Opreturn do_iastore(OPENV *env)
{
    IASTORE(env, int);
    RETURNV;
}
Opreturn do_lastore(OPENV *env)
{
    XASTOREL(env, long);
    RETURNV;
}
Opreturn do_fastore(OPENV *env)
{
    XASTORE(env, float);
    RETURNV;
}
Opreturn do_dastore(OPENV *env)
{
    XASTOREL(env, double);
    RETURNV;
}
Opreturn do_aastore(OPENV *env)
{
    XASTORE(env, Reference);
    RETURNV;
}
Opreturn do_bastore(OPENV *env)
{
    XASTORE(env, char);
    RETURNV;
}
Opreturn do_castore(OPENV *env)
{
    CASTORE(env, char);
    RETURNV;
}
Opreturn do_sastore(OPENV *env)
{
    XASTORE(env, short);
    RETURNV;
}

#endif
