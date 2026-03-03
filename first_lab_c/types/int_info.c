#include "int_info.h"
#include <string.h>
#include <stdio.h>
#include "data.h"

static void sum_int(const void* a, const void*b, void* out){
    const int* a1 = (const int*)a;
    const int* b1 = (const int*)b;
    int* rez = (int*)out;
    *rez = *a1 + *b1;
}

static void mull_int(const void* a, const void* b, void* out) {
    const int* x = (const int*)a;
    const int* y = (const int*)b;
    int* rez      = (int*)out;
    *rez = *x * *y;
}

static void print_element_int(const void* elem) {
    printf("%d", *(const int*)elem);
}

static TypeInfo INT_TYPEINFO;
int INT_INIT_TYPEINFO = 0;
const TypeInfo* GetIntInfo(void){
    if (INT_INIT_TYPEINFO != 1){
        INT_INIT_TYPEINFO = 1;
        INT_TYPEINFO.size = sizeof(int);
        INT_TYPEINFO.sum = sum_int;
        INT_TYPEINFO.mull = mull_int;
        INT_TYPEINFO.print_element = print_element_int;
    }
    return &INT_TYPEINFO;
}
