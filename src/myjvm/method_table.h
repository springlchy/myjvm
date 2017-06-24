/**
 * +-----------------------------------------------------------------+
 * |  myjvm writing a Java virtual machine step by step (C version)  |
 * +-----------------------------------------------------------------+
 * |  Author: springlchy <sisbeau@126.com>  All Rights Reserved      |
 * +-----------------------------------------------------------------+
 */

#ifndef METHOD_TABLE_H
#define METHOD_TABLE_H

/**
  * this file helps to implement the `invokevirtual` instruction
  */
typedef struct _MethodEntry {
    Class *pclass;
    method_info *method;
    struct _MethodEntry *next;
} MethodEntry;

typedef struct _MethodTable {
    MethodEntry *head;
    MethodEntry *tail;
} MethodTable;

MethodEntry* newMethodEntry(Class *pclass, method_info *method)
{
    MethodEntry *mte = (MethodEntry*)malloc(sizeof(MethodEntry));
    mte->pclass = pclass;
    mte->method = method;
    mte->next   = NULL;

    return mte;
}

MethodTable* newMethodTable()
{
    MethodTable* mtable = (MethodTable*)malloc(sizeof(MethodTable));
    mtable->head = mtable->tail = NULL;

    return mtable;
}

void addMethodEntry(MethodTable *mtable, MethodEntry *mte)
{
    if (NULL == mtable->head) {
        mtable->head = mte;
        mtable->tail = mte;
    } else {
        mtable->tail->next = mte;
        mtable->tail = mte;
    }
}

MethodEntry* findMethodEntry(MethodTable *mtable, Class *pclass)
{
    MethodEntry *mte = mtable->head;
    while (mte != NULL) {
        if (mte->pclass == pclass) {
            break;
        }
        mte = mte->next;
    }

    return mte;
}

#endif // METHOD_TABLE_H
