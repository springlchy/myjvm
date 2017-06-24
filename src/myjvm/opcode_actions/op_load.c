#ifndef OP_LOAD_C
#define OP_LOAD_C

#include "opcode.h"
#include "op_core.h"
#include "structs.h"

Opreturn do_iload(OPENV *env)
{
    printf(" %d", TO_CHAR(env->pc));
    ushort index = (ushort)(TO_CHAR(env->pc));
    ILOAD(env, index);

    INC_PC(env->pc);
    RETURNV;
}
Opreturn do_lload(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    ushort index = (ushort)(TO_CHAR(env->pc));
    LLOAD(env, index);

    INC_PC(env->pc);
    RETURNV;
}
Opreturn do_fload(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    ushort index = (ushort)(TO_CHAR(env->pc));
    FLOAD(env, index);

    INC_PC(env->pc);
    RETURNV;
}
Opreturn do_dload(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    ushort index = (ushort)(TO_CHAR(env->pc));
    DLOAD(env, index);

    INC_PC(env->pc);
    RETURNV;
}
Opreturn do_aload(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    ushort index = (ushort)(TO_CHAR(env->pc));
    ALOAD(env, index);

    INC_PC(env->pc);
    RETURNV;
}
Opreturn do_iload_0(OPENV *env)
{
    ILOAD(env, 0);
    RETURNV;
}
Opreturn do_iload_1(OPENV *env)
{
    ILOAD(env, 1);
    RETURNV;
}
Opreturn do_iload_2(OPENV *env)
{
    ILOAD(env, 2);
    RETURNV;
}
Opreturn do_iload_3(OPENV *env)
{
    ILOAD(env, 3);
    RETURNV;
}
Opreturn do_lload_0(OPENV *env)
{
    LLOAD(env, 0);
    RETURNV;
}
Opreturn do_lload_1(OPENV *env)
{
    LLOAD(env, 1);
    RETURNV;
}
Opreturn do_lload_2(OPENV *env)
{
    LLOAD(env, 2);
    RETURNV;
}
Opreturn do_lload_3(OPENV *env)
{
    LLOAD(env, 3);
    RETURNV;
}
Opreturn do_fload_0(OPENV *env)
{
    FLOAD(env, 0);
    RETURNV;
}
Opreturn do_fload_1(OPENV *env)
{
    FLOAD(env, 1);
    RETURNV;
}
Opreturn do_fload_2(OPENV *env)
{
    FLOAD(env, 2);
    RETURNV;
}
Opreturn do_fload_3(OPENV *env)
{
    FLOAD(env, 3);
    RETURNV;
}
Opreturn do_dload_0(OPENV *env)
{
    DLOAD(env, 0);
    RETURNV;
}
Opreturn do_dload_1(OPENV *env)
{
    DLOAD(env, 1);
    RETURNV;
}
Opreturn do_dload_2(OPENV *env)
{
    DLOAD(env, 2);
    RETURNV;
}
Opreturn do_dload_3(OPENV *env)
{
    DLOAD(env, 3);
    RETURNV;
}
Opreturn do_aload_0(OPENV *env)
{
    ALOAD(env, 0);
    RETURNV;
}
Opreturn do_aload_1(OPENV *env)
{
    ALOAD(env, 1);
    RETURNV;
}
Opreturn do_aload_2(OPENV *env)
{
    ALOAD(env, 2);
    RETURNV;
}
Opreturn do_aload_3(OPENV *env)
{
    ALOAD(env, 3);
    RETURNV;
}
Opreturn do_iaload(OPENV *env)
{
    XALOADI(env, int);
    RETURNV;
}
Opreturn do_laload(OPENV *env)
{
    XALOADL(env, long);
    RETURNV;
}
Opreturn do_faload(OPENV *env)
{
    XALOAD(env, float);
    RETURNV;
}
Opreturn do_daload(OPENV *env)
{
    XALOADL(env, double);
    RETURNV;
}
Opreturn do_aaload(OPENV *env)
{
    XALOAD(env, Reference);
    RETURNV;
}
Opreturn do_baload(OPENV *env)
{
    XALOADI(env, char);
    RETURNV;
}
Opreturn do_caload(OPENV *env)
{
    XALOADI(env, char);
    RETURNV;
}
Opreturn do_saload(OPENV *env)
{
    XALOADI(env, short);
    RETURNV;
}

#endif
