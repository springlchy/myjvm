/**
 * +-----------------------------------------------------------------+
 * |  myjvm writing a Java virtual machine step by step (C version)  |
 * +-----------------------------------------------------------------+
 * |  Author: springlchy <sisbeau@126.com>  All Rights Reserved      |
 * +-----------------------------------------------------------------+
 */

#include "jvm_debug.h"
#include "op_core.h"
#include <assert.h>

void testArray()
{
    CArray_int* arr = (CArray_int*)generalNewArray(10, 12);
    StackFrame* stf = newStackFrame(NULL, 10);
    OPENV* env = newOPENV(NULL);
    env->current_stack = stf;
    env->dbg = newDebugType(10, 20);
    PUSH_STACK(stf, arr, Reference);
    PUSH_STACK(stf, 0, int);
    PUSH_STACK(stf, 6, int);
    XASTORE(env, int);

    PUSH_STACK(stf, arr, Reference);
    PUSH_STACK(stf, 1, int);
    PUSH_STACK(stf, 9, int);
    XASTORE(env, int);

    debug("%d", arr->elements[0]);
    debug("%d", arr->elements[1]);

    PUSH_STACK(stf, arr, Reference);
    PUSH_STACK(stf, 0, int);
    XALOAD(env, int);
    debug("%d", PICK_STACK(stf, int));

    PUSH_STACK(stf, arr, ArrayRef);
    OP_ARRAY_LENGTH(env);
    debug("%d", PICK_STACK(stf, int));
}


void testFrameLocal()
{
    StackFrame* stf = newTestStackFrame(NULL, 7, 10);
    int i;
    short s;
    long l;
    float f;
    double d;

    PUT_LOCAL(stf, 0, 3656, int);
    PUT_LOCAL(stf, 1, 16, short);
    PUT_LOCAL(stf, 2, 1234567, long);
    PUT_LOCAL(stf, 4, 2.5f, float);
    PUT_LOCAL(stf, 5, 12345.678, double);

    i = GET_LOCAL(stf, 0, int);
    s = GET_LOCAL(stf, 1, short);
    l = GET_LOCAL(stf, 2, long);
    f = GET_LOCAL(stf, 4, float);
    d = GET_LOCAL(stf, 5, double);

    printf("i=%d, s=%d, l=%ld, f=%f, d=%lf\n", i, s, l, f, d);
}

void tsetFrameStack()
{
    StackFrame *stf = newTestStackFrame(NULL, 5, 10);
    int i;
    short s;
    long l;
    float f;
    double d;

    PUSH_STACK(stf, 2.67f, float);
    PUSH_STACK(stf, -1234, int);
    PUSH_STACK(stf, 1234567, long);
    PUSH_STACK(stf, 128, short);
    PUSH_STACK(stf, 4566.89, double);

    GET_STACK(stf, d, double);
    GET_STACK(stf, s, short);
    GET_STACK(stf, l, long);
    GET_STACK(stf, i, int);
    GET_STACK(stf, f, float);

    printf("d=%f, s=%d, l=%ld, i=%d, f=%f\n", d, s, l, i, f);
}

void testGetField(Class* pclass)
{
    StackFrame *stf;
    OPENV *env;
    Object *obj;

    obj = newObject(NULL, pclass);

    stf = newStackFrame(NULL, 20);
    env = newOPENV(NULL);
    env->current_class = pclass;
    env->current_obj = obj;
    env->current_stack = stf;
    env->dbg = newDebugType(20, 256);

    // push stack
    PUSH_STACKR(env->current_stack, obj, Reference);

    PUSH_STACK(env->current_stack, 1234567, int);
    POP_STACK(env->current_stack);
    PUSH_STACK(env->current_stack, -126, byte);
    OP_PUT_FIELDI(obj, 8, byte);
    printf("byte: %d\n", GET_FIELD(obj, 8, int));

    OP_GET_FIELDI(obj, 8, byte);
    printf("byte: %d\n", PICK_STACK(env->current_stack, byte));
}

void testStaticField(Class* pclass)
{
    StackFrame *stf;
    OPENV *env;
    Object *obj;

    obj = newObject(NULL,pclass);

    stf = newStackFrame(NULL, 20);
    env = newOPENV(NULL);
    env->current_class = pclass;
    env->current_obj = obj;
    env->current_stack = stf;
    env->dbg = newDebugType(20, 256);
}
