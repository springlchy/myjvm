/**
 * +-----------------------------------------------------------------+
 * |  myjvm writing a Java virtual machine step by step (C version)  |
 * +-----------------------------------------------------------------+
 * |  Author: springlchy <sisbeau@126.com>  All Rights Reserved      |
 * +-----------------------------------------------------------------+
 */

#ifndef OP_MATH_C
#define OP_MATH_C

#include "opcode.h"
#include "op_core.h"

Opreturn do_iadd(OPENV *env)
{
    IADD(env);
    RETURNV;
}
Opreturn do_ladd(OPENV *env)
{
    LADD(env);
    RETURNV;
}
Opreturn do_fadd(OPENV *env)
{
    FADD(env);
    RETURNV;
}
Opreturn do_dadd(OPENV *env)
{
    DADD(env);
    RETURNV;
}
Opreturn do_isub(OPENV *env)
{
    ISUB(env);
    RETURNV;
}
Opreturn do_lsub(OPENV *env)
{
    LSUB(env);
    RETURNV;
}
Opreturn do_fsub(OPENV *env)
{
    FSUB(env);
    RETURNV;
}
Opreturn do_dsub(OPENV *env)
{
    DSUB(env);
    RETURNV;
}
Opreturn do_imul(OPENV *env)
{
    IMUL(env);
    RETURNV;
}
Opreturn do_lmul(OPENV *env)
{
    LMUL(env);
    RETURNV;
}
Opreturn do_fmul(OPENV *env)
{
    FMUL(env);
    RETURNV;
}
Opreturn do_dmul(OPENV *env)
{
    DMUL(env);
    RETURNV;
}
Opreturn do_idiv(OPENV *env)
{
    IDIV(env);
    RETURNV;
}
Opreturn do_ldiv(OPENV *env)
{
    LDIV(env);
    RETURNV;
}
Opreturn do_fdiv(OPENV *env)
{
    FDIV(env);
    RETURNV;
}
Opreturn do_ddiv(OPENV *env)
{
    DDIV(env);
    RETURNV;
}
Opreturn do_irem(OPENV *env)
{
    IREM(env);
    RETURNV;
}
Opreturn do_lrem(OPENV *env)
{
    LREM(env);
    RETURNV;
}
Opreturn do_frem(OPENV *env)
{
    FREM(env);
    RETURNV;
}
Opreturn do_drem(OPENV *env)
{
    DREM(env);
    RETURNV;
}
Opreturn do_ineg(OPENV *env)
{
    INEG(env);
    RETURNV;
}
Opreturn do_lneg(OPENV *env)
{
    LNEG(env);
    RETURNV;
}
Opreturn do_fneg(OPENV *env)
{
    FNEG(env);
    RETURNV;
}
Opreturn do_dneg(OPENV *env)
{
    DNEG(env);
    RETURNV;
}
Opreturn do_ishl(OPENV *env)
{
    ISHL(env);
    RETURNV;
}
Opreturn do_lshl(OPENV *env)
{
    LSHL(env);
    RETURNV;
}
Opreturn do_ishr(OPENV *env)
{
    ISHR(env);
    RETURNV;
}
Opreturn do_lshr(OPENV *env)
{
    LSHR(env);
    RETURNV;
}
Opreturn do_iushr(OPENV *env)
{
    IUSHR(env);
    RETURNV;
}
Opreturn do_lushr(OPENV *env)
{
    LUSHR(env);
    RETURNV;
}
Opreturn do_iand(OPENV *env)
{
    IAND(env);
    RETURNV;
}
Opreturn do_land(OPENV *env)
{
    LAND(env);
    RETURNV;
}
Opreturn do_ior(OPENV *env)
{
    IOR(env);
    RETURNV;
}
Opreturn do_lor(OPENV *env)
{
    LOR(env);
    RETURNV;
}
Opreturn do_ixor(OPENV *env)
{
    IXOR(env);
    RETURNV;
}
Opreturn do_lxor(OPENV *env)
{
    LXOR(env);
    RETURNV;
}
Opreturn do_iinc(OPENV *env)
{
    IINC(env);
    RETURNV;
}

#endif
