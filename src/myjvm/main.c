/**
 * +-----------------------------------------------------------------+
 * |  myjvm writing a Java virtual machine step by step (C version)  |
 * +-----------------------------------------------------------------+
 * |  Author: springlchy <sisbeau@126.com>  All Rights Reserved      |
 * +-----------------------------------------------------------------+
 */

#include<stdio.h>
#include<stdlib.h>

#define DEBUG true

#include "jvm.c"
#include "test_jvm_types.c"


int main()
{
    // 0. specify the test class, the directory is specified in pass_class.c class_dir
    const char * testClassName = "test/TestStatic"; // the full qualified name of the class to be tested
    Class* pclass;
    CONSTANT_Utf8_info class_utf8_info;
    class_utf8_info.bytes =  testClassName;
    class_utf8_info.length = strlen(testClassName);

    // 1. initialize a new class table to store all loaded classes
    newLoadedClassTable();
    // 2. load the test class
    pclass = systemLoadClass(&class_utf8_info);

    // 3. store the loaded test class
    storeLoadedClass(pclass);

    // 4. run the main method of the test class
    runMainMethod(pclass);

    return 0;
}
