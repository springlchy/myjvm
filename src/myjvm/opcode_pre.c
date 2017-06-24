/**
 * +-----------------------------------------------------------------+
 * |  myjvm writing a Java virtual machine step by step (C version)  |
 * +-----------------------------------------------------------------+
 * |  Author: springlchy <sisbeau@126.com>  All Rights Reserved      |
 * +-----------------------------------------------------------------+
 */

#ifndef OPCODE_PRE_C
#define OPCODE_PRE_C

#include "opcode.h"
#include "op_core.h"

Opreturn pre_nop(OPENV *env)
{
    RETURNV;
}
Opreturn pre_aconst_nul(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iconst_m1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iconst_0(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iconst_1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iconst_2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iconst_3(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iconst_4(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iconst_5(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lconst_0(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lconst_1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fconst_0(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fconst_1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fconst_2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dconst_0(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dconst_1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_bipush(OPENV *env)
{
    PRINTD(TO_CHAR(env->pc));
    INC_PC(env->pc);
    RETURNV;
}
Opreturn pre_sipush(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTD(TO_SHORT(env->pc));
    INC2_PC(env->pc);

}
Opreturn pre_ldc(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    INC_PC(env->pc);
    RETURNV;
}
Opreturn pre_ldc_w(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
    RETURNV;
}
Opreturn pre_ldc2_w(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
    RETURNV;
}
Opreturn pre_iload(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    INC_PC(env->pc);
    RETURNV;
}
Opreturn pre_lload(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    INC_PC(env->pc);
    RETURNV;
}
Opreturn pre_fload(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    INC_PC(env->pc);
    RETURNV;
}
Opreturn pre_dload(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    INC_PC(env->pc);
    RETURNV;
}
Opreturn pre_aload(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    INC_PC(env->pc);
    RETURNV;
}
Opreturn pre_iload_0(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iload_1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iload_2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iload_3(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lload_0(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lload_1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lload_2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lload_3(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fload_0(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fload_1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fload_2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fload_3(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dload_0(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dload_1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dload_2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dload_3(OPENV *env)
{
    RETURNV;
}
Opreturn pre_aload_0(OPENV *env)
{
    RETURNV;
}
Opreturn pre_aload_1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_aload_2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_aload_3(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iaload(OPENV *env)
{
    RETURNV;
}
Opreturn pre_laload(OPENV *env)
{
    RETURNV;
}
Opreturn pre_faload(OPENV *env)
{
    RETURNV;
}
Opreturn pre_daload(OPENV *env)
{
    RETURNV;
}
Opreturn pre_aaload(OPENV *env)
{
    RETURNV;
}
Opreturn pre_baload(OPENV *env)
{
    RETURNV;
}
Opreturn pre_caload(OPENV *env)
{
    RETURNV;
}
Opreturn pre_saload(OPENV *env)
{
    RETURNV;
}
Opreturn pre_istore(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    INC_PC(env->pc);
    RETURNV;
}
Opreturn pre_lstore(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    INC_PC(env->pc);
    RETURNV;
}
Opreturn pre_fstore(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    INC_PC(env->pc);
    RETURNV;
}
Opreturn pre_dstore(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    INC_PC(env->pc);
    RETURNV;
}
Opreturn pre_astore(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    INC_PC(env->pc);
    RETURNV;
}
Opreturn pre_istore_0(OPENV *env)
{
    RETURNV;
}
Opreturn pre_istore_1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_istore_2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_istore_3(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lstore_0(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lstore_1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lstore_2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lstore_3(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fstore_0(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fstore_1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fstore_2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fstore_3(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dstore_0(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dstore_1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dstore_2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dstore_3(OPENV *env)
{
    RETURNV;
}
Opreturn pre_astore_0(OPENV *env)
{
    RETURNV;
}
Opreturn pre_astore_1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_astore_2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_astore_3(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iastore(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lastore(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fastore(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dastore(OPENV *env)
{
    RETURNV;
}
Opreturn pre_aastore(OPENV *env)
{
    RETURNV;
}
Opreturn pre_bastore(OPENV *env)
{
    RETURNV;
}
Opreturn pre_castore(OPENV *env)
{
    RETURNV;
}
Opreturn pre_sastore(OPENV *env)
{
    RETURNV;
}
Opreturn pre_pop(OPENV *env)
{
    RETURNV;
}
Opreturn pre_pop2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dup(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dup_x1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dup_x2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dup2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dup2_x1(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dup2_x2(OPENV *env)
{
    RETURNV;
}
Opreturn pre_swap(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iadd(OPENV *env)
{
    RETURNV;
}
Opreturn pre_ladd(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fadd(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dadd(OPENV *env)
{
    RETURNV;
}
Opreturn pre_isub(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lsub(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fsub(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dsub(OPENV *env)
{
    RETURNV;
}
Opreturn pre_imul(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lmul(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fmul(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dmul(OPENV *env)
{
    RETURNV;
}
Opreturn pre_idiv(OPENV *env)
{
    RETURNV;
}
Opreturn pre_ldiv(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fdiv(OPENV *env)
{
    RETURNV;
}
Opreturn pre_ddiv(OPENV *env)
{
    RETURNV;
}
Opreturn pre_irem(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lrem(OPENV *env)
{
    RETURNV;
}
Opreturn pre_frem(OPENV *env)
{
    RETURNV;
}
Opreturn pre_drem(OPENV *env)
{
    RETURNV;
}
Opreturn pre_ineg(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lneg(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fneg(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dneg(OPENV *env)
{
    RETURNV;
}
Opreturn pre_ishl(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lshl(OPENV *env)
{
    RETURNV;
}
Opreturn pre_ishr(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lshr(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iushr(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lushr(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iand(OPENV *env)
{
    RETURNV;
}
Opreturn pre_land(OPENV *env)
{
    RETURNV;
}
Opreturn pre_ior(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lor(OPENV *env)
{
    RETURNV;
}
Opreturn pre_ixor(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lxor(OPENV *env)
{
    RETURNV;
}
Opreturn pre_iinc(OPENV *env)
{
    RETURNV;
}
Opreturn pre_i2l(OPENV *env)
{
    RETURNV;
}
Opreturn pre_i2f(OPENV *env)
{
    RETURNV;
}
Opreturn pre_i2d(OPENV *env)
{
    RETURNV;
}
Opreturn pre_l2i(OPENV *env)
{
    RETURNV;
}
Opreturn pre_l2f(OPENV *env)
{
    RETURNV;
}
Opreturn pre_l2d(OPENV *env)
{
    RETURNV;
}
Opreturn pre_f2i(OPENV *env)
{
    RETURNV;
}
Opreturn pre_f2l(OPENV *env)
{
    RETURNV;
}
Opreturn pre_f2d(OPENV *env)
{
    RETURNV;
}
Opreturn pre_d2i(OPENV *env)
{
    RETURNV;
}
Opreturn pre_d2l(OPENV *env)
{
    RETURNV;
}
Opreturn pre_d2f(OPENV *env)
{
    RETURNV;
}
Opreturn pre_i2b(OPENV *env)
{
    RETURNV;
}
Opreturn pre_i2c(OPENV *env)
{
    RETURNV;
}
Opreturn pre_i2s(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lcmp(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fcmpl(OPENV *env)
{
    RETURNV;
}
Opreturn pre_fcmpg(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dcmpl(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dcmpg(OPENV *env)
{
    RETURNV;
}
Opreturn pre_ifeq(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_ifne(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_iflt(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_ifge(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_ifgt(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_ifle(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_if_icmpeq(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_if_icmpne(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_if_icmplt(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_if_icmpge(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_if_icmpgt(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_if_icmple(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_if_acmpeq(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_if_acmpne(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_goto(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_jsr(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_ret(OPENV *env)
{
    RETURNV;
}
Opreturn pre_tableswitch(OPENV *env)
{
    int default_offset, low_offset, high_offset, i, switches, paddings;
    env->pc-=1;
    paddings = 4 - (env->pc - env->pc_start)%4;
    env->pc+=paddings;

    BE2LE4(env->pc);
    default_offset = TO_INT(env->pc);
    INC4_PC(env->pc);
    BE2LE4(env->pc);
    low_offset = TO_INT(env->pc);
    INC4_PC(env->pc);
    BE2LE4(env->pc);
    high_offset = TO_INT(env->pc);
    INC4_PC(env->pc);
    printf("default=%d,low=%d,high=%d\n", default_offset, low_offset, high_offset);
    switches = high_offset - low_offset +1;
    for(i=0;i<switches;i++){
        BE2LE4(env->pc);
        printf(" %d\n", TO_INT(env->pc));
        INC4_PC(env->pc);
    }
    //exit(0);
    RETURNV;
}
Opreturn pre_lookupswitch(OPENV *env)
{
    int default_offset, padding, i, key, npairs;
    PC pc_lookup_begin;
    env->pc-=1;
    pc_lookup_begin = env->pc;
    padding = (env->pc - env->pc_start)%4;
    if (padding > 0) {
        padding = 4 - padding;
    }
    env->pc+=padding;

    BE2LE4(env->pc);
    default_offset = TO_INT(env->pc);
    INC4_PC(env->pc);

    BE2LE4(env->pc);
    npairs = TO_INT(env->pc);
    INC4_PC(env->pc);
    debug("npairs=%d", npairs);
    for(i=0; i < npairs; i++) {
        BE2LE4(env->pc);
        printf("%d ", TO_INT(env->pc));
        INC4_PC(env->pc);
        BE2LE4(env->pc);
        printf("%d\n", TO_INT(env->pc));
        INC4_PC(env->pc);
    }

    RETURNV;
}
Opreturn pre_ireturn(OPENV *env)
{
    RETURNV;
}
Opreturn pre_lreturn(OPENV *env)
{
    RETURNV;
}
Opreturn pre_freturn(OPENV *env)
{
    RETURNV;
}
Opreturn pre_dreturn(OPENV *env)
{
    RETURNV;
}
Opreturn pre_areturn(OPENV *env)
{
    RETURNV;
}
Opreturn pre_return(OPENV *env)
{
    RETURNV;
}
Opreturn pre_getstatic(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_putstatic(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_getfield(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_putfield(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_invokevirtual(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_invokespecial(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_invokestatic(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_invokeinterface(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_invokedynamic(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_new(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_newarray(OPENV *env)
{
    PRINTSD(TO_CHAR(env->pc));
    INC_PC(env->pc);
}
Opreturn pre_anewarray(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_arraylength(OPENV *env)
{
    RETURNV;
}
Opreturn pre_athrow(OPENV *env)
{
    RETURNV;
}
Opreturn pre_checkcast(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_instanceof(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTSD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_monitorenter(OPENV *env)
{
    RETURNV;
}
Opreturn pre_monitorexit(OPENV *env)
{
    RETURNV;
}
Opreturn pre_wide(OPENV *env)
{
    BE2LE4(env->pc);
    PRINTD(TO_INT(env->pc));
    INC4_PC(env->pc);
}
Opreturn pre_multianewarray(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_ifnull(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_ifnonnull(OPENV *env)
{
    BE2LE2(env->pc);
    PRINTD(TO_SHORT(env->pc));
    INC2_PC(env->pc);
}
Opreturn pre_goto_w(OPENV *env)
{
    BE2LE4(env->pc);
    PRINTD(TO_INT(env->pc));
    INC4_PC(env->pc);
}
Opreturn pre_jsr_w(OPENV *env)
{
    BE2LE4(env->pc);
    PRINTD(TO_INT(env->pc));
    INC4_PC(env->pc);
}
Opreturn pre_breakpoint(OPENV *env)
{
    PRINTD(TO_CHAR(env->pc));
}
Opreturn pre_impdep1(OPENV *env)
{
    PRINTD(TO_CHAR(env->pc));
}
Opreturn pre_impdep2(OPENV *env)
{
    PRINTD(TO_CHAR(env->pc));
}
#endif
