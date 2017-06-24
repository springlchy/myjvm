/**
 * +-----------------------------------------------------------------+
 * |  myjvm writing a Java virtual machine step by step (C version)  |
 * +-----------------------------------------------------------------+
 * |  Author: springlchy <sisbeau@126.com>  All Rights Reserved      |
 * +-----------------------------------------------------------------+
 */

#ifndef OP_CAST_C
#define OP_CAST_C

#include "opcode.h"
#include "op_core.h"

Opreturn do_i2l(OPENV *env)
{
    I2L(env);
    RETURNV;
}
Opreturn do_i2f(OPENV *env)
{
    I2F(env);
    RETURNV;
}
Opreturn do_i2d(OPENV *env)
{
    I2D(env);
    RETURNV;
}
Opreturn do_l2i(OPENV *env)
{
    L2I(env);
    RETURNV;
}
Opreturn do_l2f(OPENV *env)
{
    L2F(env);
    RETURNV;
}
Opreturn do_l2d(OPENV *env)
{
    L2D(env);
    RETURNV;
}
Opreturn do_f2i(OPENV *env)
{
    F2I(env);
    RETURNV;
}
Opreturn do_f2l(OPENV *env)
{
    F2L(env);
    RETURNV;
}
Opreturn do_f2d(OPENV *env)
{
    F2D(env);
    RETURNV;
}
Opreturn do_d2i(OPENV *env)
{
    D2I(env);
    RETURNV;
}
Opreturn do_d2l(OPENV *env)
{
    D2L(env);
    RETURNV;
}
Opreturn do_d2f(OPENV *env)
{
    D2F(env);
    RETURNV;
}
Opreturn do_i2b(OPENV *env)
{
    I2B(env);
    RETURNV;
}
Opreturn do_i2c(OPENV *env)
{
    I2C(env);
    RETURNV;
}
Opreturn do_i2s(OPENV *env)
{
    I2S(env);
    RETURNV;
}

#endif
