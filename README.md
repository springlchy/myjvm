# myjvm
Writing a Simple Java Virtual Machine Step by Step
一步一步自制Java虚拟机（C语言版）

## Introduction
该项目的目的是从零开始用C语言做一个实验性质的Java虚拟机，实现大部分JVM指令，实现基本的面向对象特性（封装、继承、多态），能够运行一个不涉及Java本地方法调用的类（不能包含未实现的指令，见下面的指令实现情况），因为涉及到Java的本地方法（native method）还是比较麻烦的，暂时没有那么多时间精力去研究。

## 项目文件介绍

* main.c 这是整个项目的入口文件。主要是加载需要运行的类，然后运行该类的main方法
* jvm.c 实现虚拟机的基本框架（如指令执行循环、方法调用）。一些复杂的指令实现（`invokespecial`,`invokevirtual`,`invokestatic`)也在这里
* parse_class.c 实现了把字节码文件解析成Class结构体，以及递归加载类
* structs.h Class结构体中的各个数据类型的结构定义（如常量池中的各种结构、method_info、field_info）
* constants.h 定义了一些常量，主要是访问控制标志、常量池种类
* my_types.h 对C中的基本数据类型重新定义了个名字
* utils.h 对读取文件做了个简单的封装（如读取一个字节（多个字节），读取一个short，读取一个int
* op_core.h 该文件抽象地实现了JVM中的各种指令，简单的指令以宏的方式实现，复杂的以函数的方式。该文件很重要！
* opcode.h 实现了指令中用到的一些方法，之所以不与op_core放在一起，是因为op_core过于庞大
* opcode.c 主要是一个结构体数组，存放JVM指令的预处理函数及实现函数，数组的下标就是指令的opcode的十进制值
* opcode_pre.c 方法区代码段的预处理函数集，主要是大小端转换
* opcode_actions.c 该文件用include把opcode_actions目录中的文件包含进来，是指令实现的函数，每遇到一个指令，就调用相应的函数执行。
* class_hash.h 简单地实现了一个HashTable结构类型和hash算法，用于保存已经加载并解析的字节码文件，rehash方法没有实现
* test_jvm_types.c 一些测试用例，为了方便在不加载字节码文件的情况下测试代码而写

## 指令实现情况

* constant系列指令（加载常量到当前操作数栈上），除`ldc`, `ldc_w`,`ldc2_w`这三条指令只实现了部分之外（字符串和对象部分没实现），其余均以实现
* load系列指令（从局部变量表中加载数据到当前操作数栈上），全部实现
* store系列指令（把当前操作数栈栈顶的数据保存到局部变量表），全部实现
* stack系列指令（操作操作数栈的），全部实现
* math系列指令（数学运算），全部实现
* conversion(cast)系列指令（类型转换），全部实现
* compare系列指令（比较跳转），全部实现
* reference系列指令（主要是关于面向对象相关的指令），除`athrow`,`checkcast`,`instanceof`,`monitorenter`,`monitorexit`,`invokedynamic`,`invokeinterface`没有实现外，其余均已实现
* control系列指令（控制转移指令），全部实现
* extend系列指令，实现了`multianewarray`,`ifnull`,`ifnotnull`,`goto_w`指令
* 保留指令，未实现

## 后话
  该项目是用业余时间做的，在QT5.0下开发，原先只是想做个解析Java字节码的程序，后来灵感一来就越写越多。
  由于时间精力有限，没有去好好组织项目结构，代码风格不是很好，请不要学习。
  不过该项目对于学习C语言和想了解Java虚拟节的人来说还是都有很大帮助的。指令的实现中大量用到了宏，把运算符、变量类型作为参数传给宏，通过宏来定义类似的函数，省了很多代码。还有各种指针转换、函数指针的运用等，分配内存时特意分配比结构体大的内存，然后让结构体中的成员指向剩余的内存。感觉有了指针真的是无所不能。对于想了解JVM的人而言，虽然商用JVM的类加载、指令的实现不一定是这样的，但至少可以从中大概知道JVM内部是什么个情况。
