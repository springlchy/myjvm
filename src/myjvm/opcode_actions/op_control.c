#ifndef OP_CONTROL_C
#define OP_CONTROL_C

#include "opcode.h"
#include "op_core.h"

Opreturn do_goto(OPENV *env)
{
    short offset = TO_SHORT(env->pc);
    env->pc+=(offset-1);
}
Opreturn do_jsr(OPENV *env)
{
    short offset = TO_SHORT(env->pc);
    PUSH_STACK(env->current_stack, offset, short);

    INC2_PC(env->pc);
}
Opreturn do_ret(OPENV *env)
{
    short index = TO_CHAR(env->pc);
    Reference ref = GET_LOCAL(env->current_stack, index, Reference);
    env->pc = (char*)ref;

    RETURNV;
}
Opreturn do_tableswitch(OPENV *env)
{
    int index, default_offset, low_offset, high_offset, padding;
    PC pc_switch_begin;
    GET_STACK(env->current_stack, index, int);
    env->pc-=1;
    pc_switch_begin = env->pc;
    padding = (env->pc - env->pc_start)%4;
    if (padding > 0) {
        padding = 4 - padding;
    }
    env->pc+=padding;
    debug("index=%d", index);

    default_offset = TO_INT(env->pc);
    INC4_PC(env->pc);
    low_offset = TO_INT(env->pc);
    INC4_PC(env->pc);
    high_offset = TO_INT(env->pc);
    INC4_PC(env->pc);

    debug("default=%d,low=%d,high=%d\n", default_offset, low_offset, high_offset);
    if (index < low_offset || index > high_offset) {
        env->pc = pc_switch_begin + default_offset;
    } else {
        env->pc += ((index-low_offset)<<2);
        debug("jump offset: %d", TO_INT(env->pc));
        env->pc = pc_switch_begin + TO_INT(env->pc);
    }
    RETURNV;
}
Opreturn do_lookupswitch(OPENV *env)
{
    int default_offset, padding, i, key, npairs;
    PC pc_lookup_begin;
    GET_STACK(env->current_stack, key, int);
    env->pc-=1;
    pc_lookup_begin = env->pc;
    padding = (env->pc - env->pc_start)%4;
    if (padding > 0) {
        padding = 4 - padding;
    }
    env->pc+=padding;

    default_offset = TO_INT(env->pc);
    INC4_PC(env->pc);
    npairs = TO_INT(env->pc);
    INC4_PC(env->pc);

    for(i = 0; i < npairs; i++) {
        if (key == TO_INT(env->pc)) {
            INC4_PC(env->pc);
            env->pc = pc_lookup_begin + TO_INT(env->pc);
            debug("jump=%d", env->pc - env->pc_start);
            RETURNV;
        } else {
            INC8_PC(env->pc);
        }
    }

    env->pc = pc_lookup_begin + default_offset;
    debug("default jump=%d", env->pc-env->pc_start);

    RETURNV;
}

Opreturn do_ireturn(OPENV *env)
{
    int v;
    GET_STACK(env->current_stack, v, int);
    PUSH_STACK(env->current_stack->prev, v, int);
    debug("method call end, returns: %d", v);
    FUNC_RETURN(env);
    RETURNV;
}
Opreturn do_lreturn(OPENV *env)
{
    long v;
    GET_STACKL(env->current_stack,v, long);
    PUSH_STACKL(env->current_stack->prev, v, long);
    debug("method call end, returns: %ld", v);
    FUNC_RETURN(env);
    RETURNV;
}
Opreturn do_freturn(OPENV *env)
{
    float v;
    GET_STACK(env->current_stack, v, float);
    PUSH_STACK(env->current_stack->prev, v, float);
    debug("method call end, returns: %f", v);
    FUNC_RETURN(env);
    RETURNV;
}
Opreturn do_dreturn(OPENV *env)
{
    double v;
    GET_STACKL(env->current_stack,v, double);
    PUSH_STACKL(env->current_stack->prev, v, double);
    debug("method call end, returns: %lf", v);
    FUNC_RETURN(env);
    RETURNV;
}
Opreturn do_areturn(OPENV *env)
{
    Reference v;
    GET_STACK(env->current_stack,v, Reference);
    PUSH_STACK(env->current_stack->prev, v, Reference);
    debug("method call end, returns: 0x%p", v);
    FUNC_RETURN(env);
    RETURNV;
}
Opreturn do_return(OPENV *env)
{
    // return void
    debug("method call end, returns void",3);
    FUNC_RETURN(env);
    RETURNV;
}

#endif
