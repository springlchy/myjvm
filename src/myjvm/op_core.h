#ifndef OP_CORE_H
#define OP_CORE_H

#include <stdio.h>
#include <errno.h>
#include <error.h>

#include "structs.h"
#include "jvm_debug.h"
#include "opcode.h"


/** float comparison precision **/
#define EPISILON 0.00000001

/** stack of stack frame **/
#define STACK_FRAME_SIZE 256
#define SZ_INT sizeof(int)
#define SZ_LONG (sizeof(int)<<1)
#define SZ_REF sizeof(int*)
#define SP_STEP SZ_INT
#define SP_STEP_LONG SZ_LONG
#define SP_STEP_DLONG (SZ_LONG<<1)
#define SP_STEP_ILONG (SZ_LONG+SZ_INT)

#ifdef DEBUG
#define SHOW_SP(stack) debug("[sp=%p]", stack->sp)
#else
#define SHOW_SP(stack)
#endif

#define SP_UP(stack) (stack->sp)+=SP_STEP
#define SP_DOWN(stack) (stack->sp)-=SP_STEP
#define SP_UPL(stack) (stack->sp)+=SP_STEP_LONG
#define SP_DOWNL(stack) (stack->sp)-=SP_STEP_LONG
#define SP_DOWNIL(stack) (stack->sp)-=SP_STEP_ILONG
#define SP_DOWNDL(stack) (stack->sp)-=SP_STEP_DLONG
#define SP_DOWN_POS(stack) (stack->sp-SP_STEP)
#define SP_DOWN_POSL(stack) (stack->sp-SP_STEP_LONG)

#define PUSH_STACK(stack, v, vtype)  {debug("before push:sp=%p, v=%d",stack->sp, v);\
    *(vtype*)(stack->sp)=v;\
    SP_UP(stack);\
    SHOW_SP(stack);\
}
#define PUSH_STACKL(stack, v, vtype) *((vtype*)(stack->sp)) = v;\
    SP_UPL(stack);SHOW_SP(stack)
#define PUSH_STACKR(stack, v, vtype) *((vtype*)(stack->sp)) = v;\
    SP_UP(stack);SHOW_SP(stack);
#define PICK_STACK(stack, vtype)  (*(vtype*)(stack->sp-SP_STEP))
#define PICK_STACKL(stack, vtype) (*(vtype*)(stack->sp-SP_STEP_LONG))
#define PICK_STACKIL(stack, vtype) (*(vtype*)(stack->sp-SP_STEP_ILONG))
#define PICK_STACKDL(stack, vtype) (*(vtype*)(stack->sp-SP_STEP_DLONG))
#define PICK_STACKR(stack, vtype) (*(vtype*)(stack->sp-SP_STEP))
#define PICK_STACKC(stack, vtype) (*(vtype*)(stack->sp))
#define PICK_STACKU(stack, vtype) (*(vtype*)(stack->sp+SP_STEP))
#define PICK_STACKUL(stack, vtype) (*(vtype*)(stack->sp+SP_STEP_LONG))

#define POP_STACK(stack) SP_DOWN(stack)
#define POP_STACKL(stack) SP_DOWNL(stack)
#define GET_STACK(stack,result,vtype)  SP_DOWN(stack);\
    result=PICK_STACKC(stack,vtype);\
    SHOW_SP(stack)
#define GET_STACKL(stack,result,vtype) SP_DOWNL(stack);\
    result=PICK_STACKC(stack,vtype);\
    SHOW_SP(stack)
#define GET_STACKR(stack,result,vtype) SP_DOWN(stack);\
    result=PICK_STACKC(stack,vtype);\
    SHOW_SP(stack)

#define STACK_EMPTY(stack) (stack->sp == stack->sp_base)

/** local variable in stack frame **/
#define GET_LV_OFFSET(index) ((index) << 2)
#define PUT_LOCAL(stack,vindex,v,vtype) *((vtype*)(stack->localvars + GET_LV_OFFSET(vindex)))=v

#define GET_LOCAL(stack,vindex,vtype) *((vtype*)(stack->localvars + GET_LV_OFFSET(vindex)))

/** object field manipulation **/
#define GET_FIELD_OFFSET(index) ((index) << 2)
#define GET_FIELD_ADDR(index) (obj->fields + GET_FIELD_OFFSET(findex))
#define GET_FIELD(obj, findex, ftype) *((ftype*)(obj->fields + GET_FIELD_OFFSET(findex)))
#define PUT_FIELD(obj, findex, fvalue, ftype) *((ftype*)(obj->fields + GET_FIELD_OFFSET(findex)))=fvalue

#define OP_GET_FIELDI(obj, findex, ftype) PUSH_STACK(env->current_stack, GET_FIELD(obj, findex, ftype), int)
#define OP_GET_FIELDF(obj, findex, ftype) PUSH_STACK(env->current_stack, GET_FIELD(obj, findex, ftype), float)
#define OP_GET_FIELDL(obj, findex, ftype) PUSH_STACKL(env->current_stack, GET_FIELD(obj, findex, ftype), ftype)
#define OP_GET_FIELDR(obj, findex, ftype) PUSH_STACK(env->current_stack, GET_FIELD(obj, findex, ftype), Reference)

#define OP_PUT_FIELDI(obj, findex, ftype) obj=PICK_STACKL(env->current_stack, Reference);\
    SP_DOWNL(env->current_stack);\
    PUT_FIELD(obj, findex, PICK_STACKU(env->current_stack, ftype), int)

#define OP_PUT_FIELDF(obj, findex, ftype) obj=PICK_STACKL(env->current_stack, Reference);\
    SP_DOWNL(env->current_stack);\
    PUT_FIELD(obj, findex, PICK_STACKU(env->current_stack, ftype), float)

#define OP_PUT_FIELDL(obj, findex, ftype) obj=PICK_STACKIL(env->current_stack, Reference);\
    SP_DOWNIL(env->current_stack);\
    PUT_FIELD(obj, findex, PICK_STACKU(env->current_stack, ftype), ftype)

#define OP_PUT_FIELDR(obj, findex, ftype) obj=PICK_STACKL(env->current_stack, Reference);\
    SP_DOWNL(env->current_stack);\
    PUT_FIELD(obj, findex, PICK_STACKU(env->current_stack, ftype), Reference)

#define GET_STATIC_FIELD(pclass, findex, ftype) *(ftype*)(pclass->static_fields+(findex<<2))
#define OP_GET_STATIC_FIELDI(pclass, findex, ftype) PUSH_STACK(env->current_stack, GET_STATIC_FIELD(pclass, findex, ftype), int);
#define OP_GET_STATIC_FIELDF(pclass, findex, ftype) PUSH_STACK(env->current_stack, GET_STATIC_FIELD(pclass, findex, ftype), float);
#define OP_GET_STATIC_FIELDL(pclass, findex, ftype) PUSH_STACKL(env->current_stack, GET_STATIC_FIELD(pclass, findex, ftype), ftype);
#define OP_GET_STATIC_FIELDR(pclass, findex, ftype) PUSH_STACK(env->current_stack, GET_STATIC_FIELD(pclass, findex, ftype), ftype);

#define PUT_STATIC_FIELD(pclass, findex, fvalue, ftype) *(ftype*)(pclass->static_fields+(findex<<2))=fvalue
#define OP_PUT_STATIC_FIELDI(pclass, findex, ftype) PUT_STATIC_FIELD(pclass, findex, PICK_STACK(env->current_stack, ftype), ftype);\
    SP_DOWN(env->current_stack)
#define OP_PUT_STATIC_FIELDF(pclass, findex, ftype) PUT_STATIC_FIELD(pclass, findex, PICK_STACK(env->current_stack, ftype), ftype);\
    SP_DOWN(env->current_stack)
#define OP_PUT_STATIC_FIELDL(pclass, findex, ftype) PUT_STATIC_FIELD(pclass, findex, PICK_STACKL(env->current_stack, ftype), ftype);\
    SP_DOWNL(env->current_stack)
#define OP_PUT_STATIC_FIELDR(pclass, findex, ftype) PUT_STATIC_FIELD(pclass, findex, PICK_STACK(env->current_stack, ftype), ftype);\
    SP_DOWN(env->current_stack)


/** opcode micros **/
/** 1. xload **/
#define XLOAD(env, index, xtype) PUSH_STACK(env->current_stack, GET_LOCAL(env->current_stack, index, xtype), xtype)
#define XLOADL(env, index, xtype) PUSH_STACKL(env->current_stack, GET_LOCAL(env->current_stack, index, xtype), xtype)
#define XLOADR(env, index, xtype) PUSH_STACKR(env->current_stack, GET_LOCAL(env->current_stack, index, xtype), xtype)

#define ILOAD(env, index) XLOAD(env, index, int);\
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_i);\
    DEBUG_SP_UP(env->dbg)
#define LLOAD(env, index) XLOADL(env, index, long);\
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_l);\
    DEBUG_SP_UP(env->dbg)
#define FLOAD(env, index) XLOAD(env, index, float);\
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_f);\
    DEBUG_SP_UP(env->dbg)
#define DLOAD(env, index) XLOADL(env, index, double);\
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_d);\
    DEBUG_SP_UP(env->dbg)
#define ALOAD(env, index) XLOADR(env, index, Reference);\
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_r);\
    DEBUG_SP_UP(env->dbg)

/** 2. xstore **/
#define XSTORE(env, index, xtype) PUT_LOCAL(env->current_stack, index, PICK_STACK(env->current_stack, xtype), xtype);\
    POP_STACK(env->current_stack)
#define XSTOREL(env, index, xtype) PUT_LOCAL(env->current_stack, index, PICK_STACKL(env->current_stack, xtype), xtype);\
    POP_STACKL(env->current_stack)

#define ISTORE(env, index) XSTORE(env, index, int);\
    debug("ISTORE:%d", PICK_STACKC(env->current_stack, int));\
    DEBUG_SET_LV_TYPE(env->dbg, index, debug_type_i);\
    DEBUG_SP_DOWN(env->dbg)
#define LSTORE(env, index) XSTOREL(env, index, long);\
    DEBUG_SET_LV_TYPE(env->dbg, index, debug_type_l);\
    DEBUG_SP_DOWN(env->dbg)
#define FSTORE(env, index) XSTORE(env, index, float);\
    debug("FSTORE:%f", PICK_STACKC(env->current_stack, float));\
    DEBUG_SET_LV_TYPE(env->dbg, index, debug_type_f);\
    DEBUG_SP_DOWN(env->dbg)
#define DSTORE(env, index) XSTOREL(env, index, double);\
    debug("DSTORE: index=%d, value=%lf", index, GET_LOCAL(env->current_stack, index, double));\
    DEBUG_SET_LV_TYPE(env->dbg, index, debug_type_d);\
    DEBUG_SP_DOWN(env->dbg)
#define ASTORE(env, index) XSTORE(env, index, Reference);\
    DEBUG_SET_LV_TYPE(env->dbg, index, debug_type_r);\
    DEBUG_SP_DOWN(env->dbg)

/** 3. xaload **/
#define XALOAD(env, xtype) {int index;\
    CArray_##xtype *arr_ref;\
    GET_STACK(env->current_stack, index, int);\
    GET_STACKR(env->current_stack, arr_ref, CArray_##xtype*);\
    PUSH_STACK(env->current_stack, ARRAY_INDEX(arr_ref,index), xtype);\
    DEBUG_SP_DOWNL(env->dbg);\
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_r);}
#define XALOADI(env, xtype) {int index;\
    CArray_##xtype *arr_ref;\
    GET_STACK(env->current_stack, index, int);\
    GET_STACKR(env->current_stack, arr_ref, CArray_##xtype*);\
    debug("XALOADI arr_ref=%p, index=%d", arr_ref, index);\
    PUSH_STACK(env->current_stack, ARRAY_INDEX(arr_ref,index), int);\
    DEBUG_SP_DOWNL(env->dbg);\
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_r);}

#define XALOADL(env, xtype) {int index;\
    CArray_##xtype *arr_ref;\
    GET_STACK(env->current_stack, index, int);\
    GET_STACKR(env->current_stack, arr_ref, CArray_##xtype*);\
    PUSH_STACKL(env->current_stack, ARRAY_INDEX(arr_ref,index), xtype);\
    DEBUG_SP_DOWNL(env->dbg);\
    DEBUG_SET_SP_TYPE(env->dbg, debug_type_r);}

/** 4. xastore **/
#define XASTORE(env, xtype) {xtype v;\
    int index;\
    CArray_##xtype *arr_ref;\
    GET_STACK(env->current_stack, v, xtype);\
    GET_STACK(env->current_stack, index, int);\
    GET_STACK(env->current_stack, arr_ref, CArray_##xtype*);\
    ARRAY_INDEX(arr_ref,index) = v;\
    DEBUG_SP_DOWNT(env->dbg);}

#define IASTORE(env, xtype) {xtype v;\
    int index;\
    CArray_##xtype *arr_ref;\
    GET_STACK(env->current_stack, v, xtype);\
    GET_STACK(env->current_stack, index, int);\
    GET_STACK(env->current_stack, arr_ref, CArray_int*);\
    debug("arr_ref=%p,*arr_ref=%p, index=%d, v=%d", arr_ref, *arr_ref, index, v);\
    ARRAY_INDEX(arr_ref,index) = v;\
    DEBUG_SP_DOWNT(env->dbg);}

#define CASTORE(env, xtype) {xtype v;\
    int index;\
    CArray_##xtype *arr_ref;\
    GET_STACK(env->current_stack, v, xtype);\
    GET_STACK(env->current_stack, index, int);\
    GET_STACKR(env->current_stack, arr_ref, CArray_##xtype*);\
    ARRAY_INDEX(arr_ref,index) = v;\
    debug("CASTORE index=%d,c=%c, ->%c", index, v, ARRAY_INDEX(arr_ref, index));\
    DEBUG_SP_DOWNT(env->dbg);}

#define XASTOREL(env, xtype) {xtype v;\
    int index;\
    CArray_##xtype *arr_ref;\
    GET_STACKL(env->current_stack, v, xtype);\
    GET_STACK(env->current_stack, index, int);\
    GET_STACKR(env->current_stack, arr_ref, CArray_##xtype*);\
    ARRAY_INDEX(arr_ref,index) = v;\
    DEBUG_SP_DOWNT(env->dbg);}

/** 5. math and logic op **/
//#define XOP(env, xtype, OP) xtype result;\
//    result = PICK_STACKL(env->current_stack, xtype) OP PICK_STACK(env->current_stack, xtype);\
//    SP_DOWNL(env->current_stack);\
//    PUSH_STACK(env->current_stack,result, xtype);\
//    DEBUG_SP_DOWN(env->dbg)

//#define XOPL(env, xtype, OP) xtype result;\
//    result = PICK_STACKDL(env->current_stack, xtype) OP PICK_STACKL(env->current_stack, xtype);\
//    SP_DOWNDL(env->current_stack);\
//    PUSH_STACKL(env->current_stack,result, xtype);\
//    DEBUG_SP_DOWN(env->dbg)

#define XOP(env, xtype, OP) SP_DOWNL(env->current_stack);\
    PUSH_STACK(env->current_stack,(PICK_STACKC(env->current_stack, xtype) OP PICK_STACKU(env->current_stack, xtype)), xtype);\
    DEBUG_SP_DOWN(env->dbg)

#define XOPL(env, xtype, OP) SP_DOWNDL(env->current_stack);\
    PUSH_STACKL(env->current_stack,(PICK_STACKC(env->current_stack, xtype) OP PICK_STACKUL(env->current_stack, xtype)), xtype);\
    DEBUG_SP_DOWN(env->dbg)


#define XNEG(env, xtype) SP_DOWN(env->current_stack);\
    PUSH_STACK(env->current_stack, -(PICK_STACKC(env->current_stack, xtype)), xtype)

#define XNEGL(env, xtype) SP_DOWNL(env->current_stack);\
    PUSH_STACKL(env->current_stack, -(PICK_STACKC(env->current_stack, xtype)), xtype)

#define IADD(env) debug("v1=%d, v2=%d", PICK_STACKL(env->current_stack, int), PICK_STACK(env->current_stack, int));\
    XOP(env, int, +)
#define ISUB(env) XOP(env, int, -)
#define IMUL(env) XOP(env, int, *)
#define IDIV(env) XOP(env, int, /)
#define IREM(env) XOP(env, int, %)

#define FADD(env) debug("v1=%f, v2=%f", PICK_STACKL(env->current_stack, float), PICK_STACK(env->current_stack, float));\
    XOP(env, float, +)
#define FSUB(env) XOP(env, float, -)
#define FMUL(env) XOP(env, float, *)
#define FDIV(env) XOP(env, float, /)
#define FREM(env) float v1,v2;\
    GET_STACK(env->current_stack, v2, float);\
    GET_STACK(env->current_stack, v1, float);\
    v1 = v1 - v1/v2;\
    PUSH_STACK(env->current_stack, v1, float);\
    DEBUG_SP_DOWN(env->dbg)


#define LADD(env) debug("v1=%ld, v2=%ld", PICK_STACKDL(env->current_stack, long), PICK_STACKL(env->current_stack, long));\
    XOPL(env, long, +)
#define LSUB(env) XOPL(env, long, -)
#define LMUL(env) XOPL(env, long, *)
#define LDIV(env) XOPL(env, long, /)
#define LREM(env) XOPL(env, long, %)

#define DADD(env) debug("v1=%lf, v2=%lf", PICK_STACKDL(env->current_stack, double), PICK_STACKL(env->current_stack, double));\
    XOPL(env, double, +)
#define DSUB(env) XOPL(env, double, -)
#define DMUL(env) XOPL(env, double, *)
#define DDIV(env) debug("DDIV: v1=%lf, v2=%lf", PICK_STACKDL(env->current_stack, double), PICK_STACKL(env->current_stack, double));\
    XOPL(env, double, /)
#define DREM(env) double v1,v2;\
    GET_STACKL(env->current_stack, v2, double);\
    GET_STACKL(env->current_stack, v1, double);\
    v1 = v1 - v1/v2;\
    PUSH_STACKL(env->current_stack, v1, double);\
    DEBUG_SP_DOWN(env->dbg)

#define INEG(env) XNEG(env, int)
#define FNEG(env) XNEG(env, float)
#define LNEG(env) XNEGL(env, long)
#define DNEG(env) XNEGL(env, double)

#define IAND(env) XOP(env, int, &&)
#define IOR(env)  XOP(env, int, ||)
#define IXOR(env) XOP(env, int, ^)

#define LAND(env) XOPL(env, long, &&)
#define LOR(env)  XOPL(env, long, ||)
#define LXOR(env) XOPL(env, long, ^)

#define IINC(env) GET_LOCAL(env->current_stack, TO_CHAR(env->pc), int)+=(TO_BYTE(env->pc+1));\
    env->pc+=2

#define ISH(env, OP) int result;\
    result = PICK_STACKL(env->current_stack, int) OP (PICK_STACK(env->current_stack, int) & 0x1f);\
    SP_DOWNL(env->current_stack);\
    PUSH_STACK(env->current_stack,result, int);\
    DEBUG_SP_DOWN(env->dbg)
#define ISHL(env) ISH(env, <<)
#define ISHR(env) ISH(env, >>)

#define LSH(env, OP) long v1;int v2;\
    GET_STACK(env->current_stack, v2, int);\
    GET_STACKL(env->current_stack, v1, long);\
    PUSH_STACKL(env->current_stack, v1 OP (v2 & 0x3f), long);\
    DEBUG_SP_DOWN(env->dbg)
#define LSHL(env) LSH(env, <<)
#define LSHR(env) LSH(env, >>)

#define IUSHR(env) int v1, v2;\
    GET_STACK(env->current_stack, v2, int);\
    GET_STACK(env->current_stack, v1, int);\
    v1 = (unsigned int)v1;\
    PUSH_STACK(env->current_stack,((v1) >> (v2 & 0x1f)), int);\
    DEBUG_SP_DOWN(env->dbg)

#define LUSHR(env) long v1; int v2;\
    GET_STACK(env->current_stack, v2, int);\
    GET_STACKL(env->current_stack, v1, long);\
    v1 = (unsigned long)v1;\
    PUSH_STACKL(env->current_stack,((v1) << (v2 & 0x3f)), long);\
    DEBUG_SP_DOWN(env->dbg)

/** 6. type converstion **/
#define type1i_2_type2i(env, type1, type2) SP_DOWN(env->current_stack);\
    PUSH_STACK(env->current_stack, (type2)(PICK_STACKC(env->current_stack, type1)), type2)
#define type1i_2_type2l(env, type1, type2) SP_DOWN(env->current_stack);\
    PUSH_STACKL(env->current_stack, (type2)(PICK_STACKC(env->current_stack, type1)), type2)
#define type1l_2_type2i(env, type1, type2) SP_DOWNL(env->current_stack);\
    PUSH_STACK(env->current_stack, (type2)(PICK_STACKC(env->current_stack, type1)), type2)
#define type1l_2_type2l(env, type1, type2) SP_DOWNL(env->current_stack);\
    PUSH_STACKL(env->current_stack, (type2)(PICK_STACKC(env->current_stack, type1)), type2)

#define I2L(env) type1i_2_type2l(env, int, long);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_l)
#define I2F(env) type1i_2_type2i(env, int, float);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_f)
#define I2D(env) type1i_2_type2l(env, int, double);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_d)

#define L2I(env) type1l_2_type2i(env, long, int);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_i)
#define L2F(env) type1l_2_type2i(env, long, float);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_f)
#define L2D(env) type1l_2_type2l(env, long, double);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_d)

#define F2I(env) type1i_2_type2i(env, float, int);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_i)
#define F2L(env) type1i_2_type2l(env, float, long);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_l)
#define F2D(env) type1i_2_type2l(env, float, double);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_d)

#define D2I(env) type1l_2_type2i(env, double, int);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_i)
#define D2L(env) type1l_2_type2l(env, double, long);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_l)
#define D2F(env) type1l_2_type2i(env, double, float);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_f)

#define I2B(env) type1i_2_type2i(env, int, char);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_c)
#define I2C(env) type1i_2_type2i(env, int, char);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_c)
#define I2S(env) type1i_2_type2i(env, int, short);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_s)

/** 7. comparisons **/
#define LCMP(env) long v1,v2,result; int i;\
    GET_STACKL(env->current_stack, v2, long);\
    GET_STACKL(env->current_stack, v1, long);\
    result = v1 - v2;\
    i = (result > 0 ? 1 : (result == 0 ? 0 : -1));\
    PUSH_STACK(env->current_stack, i, int)

#define FCMPL(env) float v1,v2,result; int i;\
    GET_STACK(env->current_stack, v2, float);\
    GET_STACK(env->current_stack, v1, float);\
    result = v1 - v2;\
    i = (result > 0 ? 1 : (result <= EPISILON ? 0 : -1));\
    PUSH_STACK(env->current_stack, i, int);\
    DEBUG_SP_DOWN(env->dbg);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_i)

#define FCMPG(env) float v1,v2,result; int i;\
    GET_STACK(env->current_stack, v2, float);\
    GET_STACK(env->current_stack, v1, float);\
    result = v1 - v2;\
    i = (result > 0 ? 1 : (result <= EPISILON ? 0 : -1));\
    PUSH_STACK(env->current_stack, i, int);\
    DEBUG_SP_DOWN(env->dbg);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_i)

#define DCMPL(env) double v1,v2,result; int i;\
    GET_STACKL(env->current_stack, v2, double);\
    GET_STACKL(env->current_stack, v1, double);\
    result = v1 - v2;\
    i = (result > 0 ? 1 : (result <= EPISILON ? 0 : -1));\
    PUSH_STACK(env->current_stack, i, int);\
    DEBUG_SP_DOWN(env->dbg);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_i)

#define DCMPG(env) double v1,v2,result; int i;\
    GET_STACKL(env->current_stack, v2, double);\
    GET_STACKL(env->current_stack, v1, double);\
    result = v1 - v2;\
    i = (result > 0 ? 1 : (result <= EPISILON ? 0 : -1));\
    PUSH_STACK(env->current_stack, i, int);\
    DEBUG_SP_DOWN(env->dbg);\
    DEBUG_CAST_SP_TYPE(env->dbg, debug_type_i)

/** 8. compare and jump **/
#define IFXEQ(env, OP) short offset;\
    int v;\
    GET_STACK(env->current_stack, v, int);\
    DEBUG_SP_DOWN(env->dbg);\
    if (v OP 0) {\
        offset = TO_SHORT(env->pc);\
        env->pc+=(offset-1);\
    } else {\
        INC2_PC(env->pc);\
    }

#define IFEQ(env) IFXEQ(env, ==)
#define IFNE(env) IFXEQ(env, !=)
#define IFLT(env) IFXEQ(env, <)
#define IFGE(env) IFXEQ(env, >=)
#define IFGT(env) IFXEQ(env, >)
#define IFLE(env) IFXEQ(env, <=)

#define ICMPXEQ(env, OP) short offset;\
    int v1,v2;\
    GET_STACK(env->current_stack, v2, int);\
    GET_STACK(env->current_stack, v1, int);\
    DEBUG_SP_DOWNL(env->dbg);\
    debug("v1=%d,v2=%d; offset=%d", v1, v2, *(short*)(env->pc));\
    if (v1 OP v2) {\
        offset = TO_SHORT(env->pc);\
        env->pc+=(offset-1);\
        debug("goto %d", env->pc-env->pc_start);;\
        system("pause");\
    } else {\
        debug("pc=%p", env->pc);\
        INC2_PC(env->pc);\
        debug("pc=%p", env->pc);\
    }

#define ICMPEQ(env) ICMPXEQ(env, ==)
#define ICMPNE(env) ICMPXEQ(env, !=)
#define ICMPLT(env) ICMPXEQ(env, <)
#define ICMPGE(env) ICMPXEQ(env, >=)
#define ICMPGT(env) ICMPXEQ(env, >)
#define ICMPLE(env) ICMPXEQ(env, <=)

#define ACMPXEQ(env, OP) short offset;\
    Reference ref1,ref2;\
    GET_STACKR(env->current_stack, ref2, Reference);\
    GET_STACKR(env->current_stack, ref1, Reference);\
    DEBUG_SP_DOWNL(env->dbg);\
    if (ref1 OP ref2) {\
        offset = TO_SHORT(env->pc);\
        env->pc+=(offset-1);\
    } else {\
        INC2_PC(env->pc);\
    }

#define ACMPEQ(env) ACMPXEQ(env, ==)
#define ACMPNE(env) ACMPXEQ(env, !=)

/** 9. control **/
#define FUNC_RETURN(env) StackFrame* stf = env->current_stack;\
    env->current_stack = stf->prev;\
    env->pc = stf->last_pc;\
    env->pc_end = stf->last_pc_end;\
    env->pc_start = stf->last_pc_start;\
    env->current_class = stf->last_class;\
    debug("back: stack=%p, sp=%p, pc=%p", stf, stf->sp, env->pc);\
    free(stf);\
    env->call_depth--;\
    if (env->current_stack == NULL) {\
        debug("END:%p", env->current_stack);\
        if (env->is_clinit) {\
            return ;\
        } else { \
            exit(0);\
        }\
    }

/** End of operations **/

typedef struct _Object {
    Class* pclass;
    int length;
    char* fields;
} Object;

typedef Object* Reference;

typedef uchar* PC;
typedef struct _StackFrame {
    struct _StackFrame *prev;
    Class* last_class;
    PC last_pc;
    PC last_pc_end;
    PC last_pc_start;
    method_info* method;
    int is_cclinit;
    int local_vars_count;
    char* localvars;
    char* sp;
    char* sp_base;
    char* sp_max;
} StackFrame;

typedef struct _OPENV {
    PC pc;
    PC pc_end;
    PC pc_start;
    StackFrame *current_stack;
    Class *current_class;
    Object *current_obj;
    method_info* method;
    DebugType* dbg;
    int call_depth;
    int is_clinit;
} OPENV;

typedef void Opreturn;
typedef Opreturn (*InstructionFun)(OPENV *env);
typedef struct _Instruction {
    const char *code_name;
    InstructionFun pre_action;
    InstructionFun action;
} Instruction;

typedef char boolean;
typedef char byte;

#define DEF_CARRAY(xtype) typedef struct _CArray_##xtype {\
    int length;\
    int atype;\
    int dimensions;\
    xtype* elements;\
} CArray_##xtype



DEF_CARRAY(boolean);
DEF_CARRAY(byte);
DEF_CARRAY(char);
DEF_CARRAY(ushort);
DEF_CARRAY(short);
DEF_CARRAY(int);
DEF_CARRAY(float);
DEF_CARRAY(long);
DEF_CARRAY(double);
DEF_CARRAY(Reference);

typedef CArray_int* ArrayRef;
DEF_CARRAY(ArrayRef);

#define ARRAY_INDEX(arr,index) (arr->elements[index])
#define ARRAY_LENGTH(arr) ((arr)->length)
#define OP_ARRAY_LENGTH(env) {ArrayRef arr_ref;\
    GET_STACK(env->current_stack, arr_ref, ArrayRef);\
    PUSH_STACK(env->current_stack, ARRAY_LENGTH(arr_ref), int);}
#define CHECK_ARRAY_INDEX(arr, index) if(index<0 || index>=ARRAY_LENGTH(arr)) {\
    printf("Invalid array index: %d\n", index);\
    exit(1);\
    }

//typedef struct _CArray_ArrayRef {\
//    int length;\
//    int atype;\
//    int dimensions;\
//    struct _CArray_ArrayRef* elements;\
//} CArray_ArrayRef;

#define NEW_CARRAY(xtype) CArray_##xtype* newCArray_##xtype(int length, int atype, int dimensions){\
    CArray_##xtype* arr_ref = (CArray_##xtype*)malloc(sizeof(CArray_##xtype) + sizeof(xtype)*length);\
    arr_ref->length = length;\
    arr_ref->atype  = atype;\
    arr_ref->dimensions = dimensions;\
    arr_ref->elements = (xtype*)(arr_ref+1);\
    return arr_ref;\
}

NEW_CARRAY(boolean)
NEW_CARRAY(byte)
//NEW_CARRAY(char)
NEW_CARRAY(ushort)
NEW_CARRAY(short)
NEW_CARRAY(int)
NEW_CARRAY(float)
NEW_CARRAY(long)
NEW_CARRAY(double)
NEW_CARRAY(Reference)

extern Class* systemLoadClass(CONSTANT_Utf8_info* class_utf8_info);
extern Class* systemLoadClassRecursive(OPENV *env, CONSTANT_Utf8_info* class_utf8_info);
void printCurrentEnv(OPENV*, const char*);

CArray_char* newCArray_char(int length, int atype, int dimensions)
{
    CArray_char* arr_ref = (CArray_char*)malloc(sizeof(CArray_char));
    arr_ref->length = length;
    arr_ref->atype = atype;
    arr_ref->dimensions = dimensions;
    arr_ref->elements = (char*)malloc(sizeof(char)*length);
    return arr_ref;
}

CArray_char* newCArray_char_fromConstStr(Class *pclass, int string_info_index)
{
    cp_info cp = pclass->constant_pool;
    CONSTANT_String_info* str_info = (CONSTANT_String_info*)(cp[string_info_index]);
    CONSTANT_Utf8_info * utf8_info = (CONSTANT_Utf8_info*)(cp[str_info->string_index]);
    CArray_char* arr_ref = (CArray_char*)malloc(sizeof(CArray_char));
    arr_ref->dimensions = 1;
    arr_ref->atype = 5;
    arr_ref->length = utf8_info->length;
    arr_ref->elements = utf8_info->bytes;

    return arr_ref;
}

extern Class* loadClass(const char*);

Object* newConstString(OPENV *env, CArray_char* char_arr)
{
    const char* string_class = "java/lang/String.class";
    CONSTANT_Utf8_info *utf8_info =(CONSTANT_Utf8_info*)malloc(sizeof(CONSTANT_Utf8_info));
    int total_size = 4;
    Object *obj;
    obj = (Object*)malloc(sizeof(Object) + ((total_size+1)<<2));

    PUSH_STACKR(env->current_stack, obj, Reference);

    obj->fields = (char*)(obj+1);
    utf8_info->bytes = "java/lang/String";
    utf8_info->length = strlen(utf8_info->bytes);
    utf8_info->tag = CONSTANT_Utf8;
    obj->pclass = systemLoadClassRecursive(env, utf8_info);

    obj->length = (total_size+1) << 2;
    PUT_FIELD(obj, 0, char_arr, CArray_char*);
    PUT_FIELD(obj, 1, 0, int);

    return obj;
}

typedef void* (*ArrayConstructor)(int,int,int);

void* generalNewArray(int arr_type, int length)
{
    ArrayConstructor arr_con;
    static ArrayConstructor array_constructors[12] = {
        NULL, // 0
        NULL,
        NULL,
        NULL,
        newCArray_boolean, // 1
        newCArray_ushort,  // 2
        newCArray_float,   // 3
        newCArray_double,  // 4
        newCArray_char,    // 5
        newCArray_short,   // 6
        newCArray_int,     // 7
        newCArray_long     // 8
    };
    if (arr_type<=0 || arr_type >= 12) {
        printf("Illegal array type: %d\n", arr_type);
        exit(1);
    }
    if (length<=0) {
        printf("Illegal array length: %d\n", length);
        exit(1);
    }
    arr_con = array_constructors[arr_type];
    return arr_con(length, arr_type, 1);
}

#define MULTI_ANEWARRAY_CALLBACK(xtype) void multianewarray_callback_##xtype(CArray_ArrayRef *sub_arr, CArray_ArrayRef **p, int ele_num, int last_dimension, int atype) {\
        CArray_##xtype* xtype##_arr;\
        int i;\
        xtype##_arr = *(CArray_##xtype**)(&sub_arr);\
        for(i=0; i<ele_num; i++) {\
            xtype##_arr->length = last_dimension;\
            xtype##_arr->elements = p;\
            xtype##_arr->dimensions = 1;\
            xtype##_arr->atype = atype;\
            p += last_dimension;\
            xtype##_arr++;\
        }\
    }

MULTI_ANEWARRAY_CALLBACK(boolean)
MULTI_ANEWARRAY_CALLBACK(byte)
MULTI_ANEWARRAY_CALLBACK(char)
MULTI_ANEWARRAY_CALLBACK(ushort)
MULTI_ANEWARRAY_CALLBACK(short)
MULTI_ANEWARRAY_CALLBACK(int)
MULTI_ANEWARRAY_CALLBACK(float)
MULTI_ANEWARRAY_CALLBACK(long)
MULTI_ANEWARRAY_CALLBACK(double)

void multianewarray_callback_Reference(CArray_ArrayRef *sub_arr, CArray_ArrayRef **p, int ele_num, int last_dimension, int atype) {
    CArray_Reference* Reference_arr;
    int i,j;
    Reference_arr = *(CArray_Reference**)(&sub_arr);
    for(i=0; i<ele_num; i++) {
        Reference_arr->length = last_dimension;
        Reference_arr->elements = p;
        Reference_arr->atype = atype;
        p += last_dimension;
        Reference_arr++;
    }
}

typedef void (*multianewarray_callback_func)(CArray_ArrayRef*, CArray_ArrayRef**, int, int, int);
typedef struct _multianewarray_callback {
    int ele_size;
    multianewarray_callback_func callback;
} MultiAnewArrayCallback;

MultiAnewArrayCallback mAnewCallaback[10] = {
  {sizeof(boolean), multianewarray_callback_boolean}, // 0
  {sizeof(byte), multianewarray_callback_byte},       // 1
  {sizeof(char), multianewarray_callback_char},       // 2
  {sizeof(ushort), multianewarray_callback_ushort},   // 3
  {sizeof(short), multianewarray_callback_short},     // 4
  {sizeof(int), multianewarray_callback_int},         // 5
  {sizeof(float), multianewarray_callback_float},     // 6
  {sizeof(long), multianewarray_callback_long},       // 7
  {sizeof(double), multianewarray_callback_double},   // 8
  {sizeof(Reference), multianewarray_callback_Reference} // 9
};

/**
 * @brief newStackFrame create a new stack frame to invoke a method
 * @param current_frame the current frame
 * @param code_attr code attribute of the method to be invoked
 * @return
 */
StackFrame* newStackFrame(StackFrame* current_frame, Code_attribute *code_attr)
{
    size_t total_size = sizeof(StackFrame) + ((code_attr->max_locals + code_attr->max_stack + 4) << 2);
    StackFrame* stf = (StackFrame*)malloc(total_size);
    memset(stf, 0, total_size);

    stf->prev = current_frame;
    stf->local_vars_count = code_attr->max_locals;
    stf->localvars = (char*)(stf + 1);
    stf->sp = stf->localvars + ((code_attr->max_locals+1) << 2);
    stf->sp_base = stf->sp;
    stf->sp_max = (char*)stf + total_size;

    return stf;
}

/**
 * @brief newTestStackFrame for test use
 * @param current_frame
 * @param max_locals
 * @param max_stack
 * @return
 */
StackFrame* newTestStackFrame(StackFrame* current_frame, int max_locals, int max_stack)
{
    size_t total_size = sizeof(StackFrame) + ((max_locals + max_stack + 4) << 2);
    StackFrame* stf = (StackFrame*)malloc(total_size);
    memset(stf, 0, total_size);

    stf->prev = current_frame;
    stf->local_vars_count = max_locals;
    stf->localvars = (char*)(stf + 1);
    stf->sp = stf->localvars + ((max_locals+1) << 2);
    stf->sp_base = stf->sp;
    return stf;
}

int getClassFieldsSize(Class *pclass) {
    int i=0;
    if (pclass->parent_fields_size >= 0) {
        return pclass->parent_fields_size + pclass->fields_size;
    } else if (pclass->parent_class == NULL) {
        pclass->parent_fields_size = 0;
        printf("top: parent_fields_size=%d, fields_size=%d\n", 0, pclass->fields_size);
        return pclass->fields_size;
    } else {
        pclass->parent_fields_size = getClassFieldsSize(pclass->parent_class);
        for(i=0; i<pclass->fields_count; i++) {
            if (NOT_ACC_STATIC((pclass->fields[i])->access_flags)) {
                (pclass->fields[i])->findex += pclass->parent_fields_size;
            }
        }
        printf("parent_fields_size=%d, fields_size=%d\n", pclass->parent_fields_size, pclass->fields_size);

        return pclass->parent_fields_size + pclass->fields_size;
    }
}

void displayThisClassFieldIndex(Class *pclass);
method_info* findClinitMethod(Class *pclass);
void runClinitMethod(OPENV *env, Class *clinit_class, method_info* method);

#define get_utf8(pool) ((CONSTANT_Utf8_info*)(pool))->bytes
#define get_this_class_name(pclass) get_utf8(pclass->constant_pool[((CONSTANT_Class_info*)(pclass->constant_pool[pclass->this_class]))->name_index])
#define get_super_class_name(pclass) get_utf8(pclass->constant_pool[((CONSTANT_Class_info*)(pclass->constant_pool[pclass->super_class]))->name_index])

/**
 * @brief newObject implements the `new` instruction
 * @param env
 * @param pclass
 * @return
 */
Object* newObject(OPENV *env, Class* pclass) {
    CONSTANT_Class_info* parent_class_info;
    Object *obj;
    Class *tmp_class;
    int i = 0, total_size = 0;

    tmp_class = pclass;
    while (tmp_class->super_class) {
        parent_class_info = (CONSTANT_Class_info*)(tmp_class->constant_pool[tmp_class->super_class]);
        if (NULL == parent_class_info->pclass) {
            parent_class_info->pclass = systemLoadClassRecursive(env, (CONSTANT_Utf8_info*)(tmp_class->constant_pool[parent_class_info->name_index]));
            tmp_class->parent_class = parent_class_info->pclass;
        }
        tmp_class = tmp_class->parent_class;
    }

    if (pclass->parent_fields_size == -1) {
        if (pclass->parent_class == NULL) {
            pclass->parent_fields_size = 0;
        } else {
            pclass->parent_fields_size = getClassFieldsSize(pclass->parent_class);
        }
        for(i=0; i<pclass->fields_count; i++) {
            if (NOT_ACC_STATIC((pclass->fields[i])->access_flags)) {
                (pclass->fields[i])->findex += pclass->parent_fields_size;
            }
        }
    }

    total_size = pclass->parent_fields_size  + pclass->fields_size;

    obj = (Object*)malloc(sizeof(Object) + ((total_size+1)<<2));

    obj->fields = (char*)(obj+1);
    obj->pclass = pclass;
    obj->length = (total_size+1) << 2;

    displayThisClassFieldIndex(pclass);

    return obj;
}

/**
 * @brief newOPENV create a new instruction execute environment
 * @return
 */
OPENV* newOPENV()
{
    OPENV *env = (OPENV*)malloc(sizeof(OPENV));
    return env;
}

/**
 * @brief print_indent
 * @param indent
 */
static void print_indent(int indent)
{
    indent = 4-indent;
    while(indent-- > 0) {
        printf("\t");
    }
}

/**
 * @brief display_arr display multidimension array recursively(for debug purpose)
 * @param arr the array to be displayed
 */
void display_arr(CArray_ArrayRef *arr)
{
    int i,j;
    CArray_ArrayRef *sub_arr;
    CArray_int *arr_int;

    print_indent(arr->dimensions+1);
    printf("dimensions=%d\n", arr->dimensions);
    for(i=0;i<arr->length;i++) {
        if (arr->dimensions > 2) {
            display_arr(arr->elements[i]);
        } else {
            arr_int = arr->elements[i];
            print_indent(arr_int->dimensions+1);
            printf("dimensions=%d\n", arr_int->dimensions);
            for(j=0;j<arr_int->length;j++) {
                print_indent(arr_int->dimensions);
                printf("i=%d,j=%d,ele=%d\n", i, j, arr_int->elements[j]);
            }
        }
    }
}

/**
 * @brief newMultiArray implements the `multianewarray` instruction
 * @param dimensions array of each dimension size, we can borrow from the operand stack to avoid copy
 * @param dcount number of dimensions
 * @param atype type of the array
 * @param manew_arr_c callback function @see MULTI_ANEWARRAY_CALLBACK
 * @return the pointer to the new allocated array
 */
CArray_ArrayRef* newMultiArray(int dimensions[], int dcount, int atype, MultiAnewArrayCallback manew_arr_c)
{
    CArray_ArrayRef **p_base,**p;
    CArray_ArrayRef *arr,  *sub_arr;
    int last_dimension = dimensions[dcount-1];
    int i=0, j=0, k=0;
    int pointer_size = 0, total_size = 0;
    int SZ_ARR = sizeof(CArray_ArrayRef);
    int arr_offset = 1;
    int ele_num=0;
    int sub_dim = dcount;
    // 0. calculate size
    if (last_dimension <= 0) {
        printf("Ilegal array size: %d\n", dimensions[i]);
        exit(1);
    }
    for(i=dcount-2; i>=0; i--) {
        if (dimensions[i] <= 0) {
            printf("Ilegal array size: %d\n", dimensions[i]);
            exit(1);
        }
        pointer_size = (pointer_size + 1) * dimensions[i];
    }

    total_size = SZ_ARR*(pointer_size+1) + pointer_size*SZ_REF + pointer_size*last_dimension*manew_arr_c.ele_size;
    arr = (CArray_ArrayRef*)malloc(total_size);
    memset(arr, 0, total_size);
    p_base = (CArray_ArrayRef*)(arr + pointer_size + 1);
    p = p_base;

    // 1.the first dimension
    arr->length = dimensions[0];
    arr->elements = p;
    arr->dimensions = sub_dim;
    arr->atype = atype;
    for(i=0; i<dimensions[0]; i++) {
        arr->elements[i] = arr + arr_offset++;
        p++;
    }

    // 2.the rest diemension except the last
    ele_num = 1;
    sub_arr = arr+1;
    for(i=0; i<dcount-2; i++) {
        sub_dim--;
        ele_num *= dimensions[i];
        for(j=0; j<ele_num; j++) {
            sub_arr->length = dimensions[i+1];
            sub_arr->elements = p;
            sub_arr->dimensions = sub_dim;
            sub_arr->atype = atype;
            for(k=0; k<sub_arr->length; k++) {
                sub_arr->elements[k] = (arr + arr_offset++);
                p++;
            }
            sub_arr++;
        }
    }

    // 3. the last dimension: data
    ele_num *=dimensions[i];

    manew_arr_c.callback(sub_arr, p, ele_num, last_dimension, atype);

    return arr;
}

/**
  * The following micro and functions are used for debug
  */
void showStackStatus(OPENV* env)
{
    DebugType *dbg = env->dbg;
    StackFrame* stack = env->current_stack;
    char* sp = stack->sp;
    short i = 0;
    short offset = 0;
    printf("\n############## Stack status ################\n");
    printf("\nstack=%p, localvar=%p:\n", stack, stack->localvars);
    for(; i<stack->local_vars_count;i++) {
        switch (dbg->localvar_base[i]) {
            case debug_type_c:
                printf(" #%d[char]=%c", i, *(char*)(stack->localvars + offset));
                offset+=SZ_INT;
                break;
            case debug_type_s:
                printf(" #%d[short]=%d", i, *(short*)(stack->localvars + offset));
                offset+=SZ_INT;
                break;
            case debug_type_i:
                printf(" #%d[int]=%d", i, *(int*)(stack->localvars + offset));
                offset+=SZ_INT;
                break;

            case debug_type_f:
                printf(" #%d[float]=%d", i, *(float*)(stack->localvars + offset));
                offset+=SZ_INT;
                break;
            case debug_type_l:
                printf(" #%d[long]=%d", i, *(long*)(stack->localvars + offset));
                offset+=SZ_LONG;
                break;
            case debug_type_d:
                printf(" #%d[double]=%d", i, *(short*)(stack->localvars + offset));
                offset+=SZ_LONG;
                break;
            case debug_type_a:
                printf(" #%d[array]=%d", i, *(short*)(stack->localvars + offset));
                offset+=SZ_INT;
                break;
            case debug_type_r:
                printf(" #%d[ref]=%d", i, *(short*)(stack->localvars + offset));
                offset+=SZ_INT;
                break;
            default:
                printf("\nError: type=%d\n", dbg->localvar_base[i]);
                exit(1);
        }
    }

    printf("\n sp_base=%p, sp=%p:\n", stack->sp_base, stack->sp);
    offset = 0;
    i = 0;
    while (dbg->spvar_base + i < dbg->spvar_type) {
        switch (dbg->spvar_base[i]) {
            case debug_type_c:
                printf(" #%d[char]=%c", i, *(char*)(stack->sp + offset));
                offset+=SZ_INT;
                break;
            case debug_type_s:
                printf(" #%d[short]=%d", i, *(short*)(stack->sp + offset));
                offset+=SZ_INT;
                break;
            case debug_type_i:
                printf(" #%d[int]=%d", i, *(int*)(stack->sp + offset));
                offset+=SZ_INT;
                break;

            case debug_type_f:
                printf(" #%d[float]=%f", i, *(float*)(stack->sp + offset));
                offset+=SZ_INT;
                break;
            case debug_type_l:
                printf(" #%d[long]=%ld", i, *(long*)(stack->sp + offset));
                offset+=SZ_LONG;
                break;
            case debug_type_d:
                printf(" #%d[double]=%lf", i, *(double*)(stack->sp + offset));
                offset+=SZ_LONG;
                break;
            case debug_type_a:
                printf(" #%d[array]=%p", i, *(ArrayRef*)(stack->sp + offset));
                offset+=SZ_REF;
                break;
            case debug_type_r:
                printf(" #%d[ref]=%p", i, *(Reference*)(stack->sp + offset));
                offset+=SZ_REF;
                break;
            default:
                printf("\nError: type=%d\n", dbg->spvar_base[i]);
            exit(1);
        }
        i++;
    }
    printf("\n############## End ################\n");
}

#define PRINT_TABN(FD, N) {int i=0;for(i=0;i<N;i++){fprintf(FD,"\t");}}
void printCurrentClassMethod(OPENV *env, Instruction instruction)
{
    int i=0;
    FILE* fp = fopen("D:/run-time.log", "a+");
    cp_info cp = env->current_class->constant_pool;
    method_info *method = env->current_stack->method;
    printf("\ncp=%p,method=%p\n", cp, method);
    CONSTANT_Utf8_info *name_utf8 = (CONSTANT_Utf8_info*)(cp[method->name_index]);
    CONSTANT_Utf8_info *desc_utf8;
    PRINT_TABN(fp, env->call_depth);
    fprintf(fp, "#%d: %s\n", env->pc-env->pc_start, instruction.code_name);
    PRINT_TABN(fp, env->call_depth);

    fprintf(fp, "current_class=%s\n", get_this_class_name(env->current_class));
    PRINT_TABN(fp, env->call_depth);
    if (strcmp(name_utf8->bytes, "<clinit>") == 0) {
        fprintf(fp, "current_method=%s\n", name_utf8->bytes);
        //system("pause");
    } else {
        desc_utf8 = (CONSTANT_Utf8_info*)(cp[method->descriptor_index]);
        fprintf(fp, "current_method=%s%s\n", name_utf8->bytes, desc_utf8->bytes);
    }
    PRINT_TABN(fp, env->call_depth);
    fprintf(fp, "stack=%p, sp=%p, sp_max=%p, pc=%p\n\n", env->current_stack, env->current_stack->sp, env->current_stack->sp_max, env->pc);
    fclose(fp);
}

void printCurrentEnv(OPENV *env, const char *label)
{
    FILE* fp = fopen("D:/run-time.log", "a+");
    PRINT_TABN(fp, env->call_depth);
    fprintf(fp, "%s: stack=%p, sp=%p, sp_max=%p, pc=%p\n", label, env->current_stack, env->current_stack->sp, env->current_stack->sp_max, env->pc);
    printf("%s: stack=%p, sp=%p, pc=%p\n", label, env->current_stack, env->current_stack->sp, env->pc);
    fclose(fp);
}
void displayStaticFields(Class *pclass)
{
    FILE* fp;
    int i=0;
    if (1 || NULL == pclass) {
        return;
    }
    fp = fopen("D:/run-time.log", "a+");
    if (!fp) {
        printf("Cannot open: D:/run-time.log\n");
        printf("errno:%d, errstr:%s\n", errno, strerror(errno));
        exit(1);
    }
    if (strcmp(get_this_class_name(pclass), "java/lang/Integer") == 0) {
        for(i=0;i<=6;i++) {
            fprintf(fp, "static fields: i=%d, %p\n", i, *(ArrayRef*)(pclass->static_fields+(i<<2)));
        }
    }
    fclose(fp);
}

#endif // OP_CORE_H
