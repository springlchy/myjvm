#ifndef CLASS_HASH_H
#define CLASS_HASH_H

static int last_hash_size = 144;
static int hash_size=233;

typedef struct _classEntry {
    int name_len;
    char *class_name;
    Class* parent_class;
    Class* pclass;

    struct _classEntry *next;
} ClassEntry;


typedef struct _classHashTable {
    int class_num;
    int hash_size;
    int used_slots;
    ClassEntry **class_array;
} ClassHashTable;

static ClassHashTable *loadedClassTable;

ClassHashTable* newClassHashTable(int size)
{
    int total_size = sizeof(ClassHashTable)+(sizeof(ClassEntry*) * size);

    ClassHashTable *classTable = (ClassHashTable*)malloc(total_size);
    memset(classTable, 0, total_size);

    classTable->hash_size = size;
    classTable->class_array = (ClassEntry**)(classTable+1);

    return classTable;
}

void newLoadedClassTable()
{
    loadedClassTable = newClassHashTable(hash_size);
}

unsigned int hash(const char* s, int hash_size)
{
    unsigned long sum=0;
    while (*s) {
        sum = (sum<<1) + *s++;
    }
    return sum % hash_size;
}
Class* findLoadedClass(const char* class_name, const int class_name_len)
{
    Class* pclass = NULL;
    ClassEntry* entry;
    unsigned int index = hash(class_name, hash_size);

    if (NULL == (entry = loadedClassTable->class_array[index])) {
        return pclass;
    }

    do {
         if (entry->name_len == class_name_len && strcmp(entry->class_name, class_name) == 0) {
             pclass = entry->pclass;
             break;
         } else {
             entry = entry->next;
         }
    } while(NULL != entry);

    return pclass;
}

int storeLoadedClass(Class* pclass)
{
    int index;
    CONSTANT_Utf8_info* utf8_info;
    CONSTANT_Class_info* class_info;
    ClassEntry* entry;
    ClassEntry* thisClassEntry = (ClassEntry*)malloc(sizeof(ClassEntry));
    class_info = (CONSTANT_Class_info*)(pclass->constant_pool[pclass->this_class]);
    utf8_info = (CONSTANT_Utf8_info*)(pclass->constant_pool[class_info->name_index]);
    thisClassEntry->name_len = utf8_info->length;
    thisClassEntry->class_name = utf8_info->bytes;
    thisClassEntry->pclass = pclass;
    thisClassEntry->next = NULL;

    index = hash(utf8_info->bytes, hash_size);
    if (NULL == loadedClassTable->class_array[index]) {
        loadedClassTable->class_array[index] = thisClassEntry;
        loadedClassTable->class_num++;
        loadedClassTable->used_slots++;
        return 0;
    }

    entry = loadedClassTable->class_array[index];
    while (entry->next != NULL) {
        entry = entry->next;
    }
    entry->next = thisClassEntry;
    loadedClassTable->class_num++;

    return 0;
}

void displayLoadedClass()
{
     int i = 0;
     ClassEntry* entry;

     printf("loadedClassTable: class_num=%d, hash_size=%d, used_slots=%d\n", loadedClassTable->class_num, loadedClassTable->hash_size, loadedClassTable->used_slots);

     for (; i < hash_size; i++) {
         if (loadedClassTable->class_array[i] != NULL) {
             printf("#%d ", i);
             entry = loadedClassTable->class_array[i];
             while (entry != NULL) {
                 printf("%s ", entry->class_name);
                 entry = entry->next;
             }
             printf("\n");
         }
     }
}

#endif // CLASS_HASH_H
