#ifndef OP_EXTEND_C
#define OP_EXTEND_C

#include "opcode.h"
#include "op_core.h"

Opreturn do_wide(OPENV *env)
{
    BE2LE4(env->pc);
    PRINTD(TO_INT(env->pc));
    INC4_PC(env->pc);
}
Opreturn do_multianewarray(OPENV *env)
{
    PRINTD(TO_SHORT(env->pc));
    cp_info cp = env->current_class->constant_pool;
    char *arr_type_utf8;
    int arr_type_index = TO_SHORT(env->pc);
    int dcount, callback_index;
    int *parr_dims;
    CArray_ArrayRef *multi_arr_ref;
    INC2_PC(env->pc);
    dcount = (int)(TO_CHAR(env->pc));
    INC_PC(env->pc);

    arr_type_utf8 = ((CONSTANT_Utf8_info*)(cp[((CONSTANT_Class_info*)(cp[arr_type_index]))->name_index]))->bytes;
    debug("arr_type_utf8=%s", arr_type_utf8);
    while(*arr_type_utf8 == '[') arr_type_utf8++;
    debug("arr_type=%s", arr_type_utf8);

    parr_dims = (int*)(env->current_stack->sp - SZ_INT*dcount);
    env->current_stack->sp = parr_dims;

    switch (*arr_type_utf8) {
    case 'B': // byte
        callback_index = 1;
        break;
    case 'C': // char
        callback_index = 2;
        break;
    case 'S': // short
        callback_index = 2;
        break;
    case 'Z': // boolean
        callback_index = 0;
        break;
    case 'I': // integer
        callback_index = 5;
        break;
    case 'F':
        callback_index = 6;
        break;
    case 'L':
        callback_index = 9;
        break;
    case 'J':
        callback_index = 7;
        break;
    case 'D':
        callback_index = 8;
        break;
    default:
        break;
    }
    multi_arr_ref = newMultiArray(parr_dims, dcount, arr_type_index & 0x10, mAnewCallaback[callback_index]);
    PUSH_STACK(env->current_stack, multi_arr_ref, CArray_ArrayRef*);
    //exit(1);
}

Opreturn do_ifnull(OPENV *env)
{
    Reference ref;
    short offset;
    GET_STACK(env->current_stack, ref, Reference);
    if (NULL == ref) {
        offset = TO_SHORT(env->pc);
        env->pc += (offset-1);
    } else {
        INC2_PC(env->pc);
    }
}
Opreturn do_ifnonnull(OPENV *env)
{
    Reference ref;
    short offset;
    GET_STACK(env->current_stack, ref, Reference);
    if (NULL != ref) {
        offset = TO_SHORT(env->pc);
        env->pc += (offset-1);
    } else {
        INC2_PC(env->pc);
    }
}

Opreturn do_goto_w(OPENV *env)
{
    int offset = TO_INT(env->pc);
    env->pc += (offset-1);
}

Opreturn do_jsr_w(OPENV *env)
{
    int addr = TO_INT(env->pc);
    PUSH_STACK(env->current_stack, addr, int);
    INC4_PC(env->pc);
}

Opreturn do_breakpoint(OPENV *env)
{
    PRINTD(TO_CHAR(env->pc));
    debug("%s", "breakpoint");
    exit(1);
    //INC_PC(env->pc);
}
Opreturn do_impdep1(OPENV *env)
{
    PRINTD(TO_CHAR(env->pc));
    debug("%s", "impdep1");
    exit(1);
    //INC_PC(env->pc);
}
Opreturn do_impdep2(OPENV *env)
{
    PRINTD(TO_CHAR(env->pc));
    debug("%s", "impdep2");
    exit(1);
    //INC_PC(env->pc);
}
#endif
