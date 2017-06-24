/**
 * +-----------------------------------------------------------------+
 * |  myjvm writing a Java virtual machine step by step (C version)  |
 * +-----------------------------------------------------------------+
 * |  Author: springlchy <sisbeau@126.com>  All Rights Reserved      |
 * +-----------------------------------------------------------------+
 */

#ifndef OP_COMPARE_C
#define OP_COMPARE_C

#include "opcode.h"
#include "op_core.h"

Opreturn do_lcmp(OPENV *env)
{
    LCMP(env);
    RETURNV;
}
Opreturn do_fcmpl(OPENV *env)
{
    FCMPL(env);
    RETURNV;
}
Opreturn do_fcmpg(OPENV *env)
{
    // TODO: different behavior of fcmpl and fcmpg to NaN
    FCMPG(env);
    RETURNV;
}
Opreturn do_dcmpl(OPENV *env)
{
    DCMPL(env);
    RETURNV;
}
Opreturn do_dcmpg(OPENV *env)
{
    // TODO: different behavior of dcmpl and dcmpg to NaN
    DCMPG(env);
    RETURNV;
}

Opreturn do_ifeq(OPENV *env)
{
    IFEQ(env);
}
Opreturn do_ifne(OPENV *env)
{
    IFNE(env);
}
Opreturn do_iflt(OPENV *env)
{
    IFLT(env);
}
Opreturn do_ifge(OPENV *env)
{
    IFGE(env);
}
Opreturn do_ifgt(OPENV *env)
{
    IFGT(env);
}
Opreturn do_ifle(OPENV *env)
{
    IFLE(env);
}
Opreturn do_if_icmpeq(OPENV *env)
{
    ICMPEQ(env);
}
Opreturn do_if_icmpne(OPENV *env)
{
    ICMPNE(env);
}
Opreturn do_if_icmplt(OPENV *env)
{
    ICMPLT(env);
}
Opreturn do_if_icmpge(OPENV *env)
{
    ICMPGE(env);
}
Opreturn do_if_icmpgt(OPENV *env)
{
    ICMPGT(env);
}
Opreturn do_if_icmple(OPENV *env)
{
    ICMPLE(env);
}
Opreturn do_if_acmpeq(OPENV *env)
{
    ACMPEQ(env);
}
Opreturn do_if_acmpne(OPENV *env)
{
    ACMPNE(env);
}

#endif
