#include "double_info.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "data.h"

static void sum_double(const void* a, const void* b, void* out){
    const double* a1 = (const double*)a;
    const double* b1 = (const double*)b;
    double* rez = (double*)out;
    *rez = *a1 + *b1;
}

static void mull_double(const void* a, const void* b, void* out){
    const double* x = (const double*)a;
    const double* y = (const double*)b;
    double* rez = (double*)out;
    *rez = (*x) * (*y);
}

static void print_element_double(const void* elem) {
    printf("%f", *(const double*)elem);
}

static TypeInfo DOUBLE_TYPEINFO;
int DOUBLE_INIT_TYPEINFO = 0;
const TypeInfo* GetDoubleInfo(void){
    if (DOUBLE_INIT_TYPEINFO != 1){
        DOUBLE_INIT_TYPEINFO = 1;
        DOUBLE_TYPEINFO.size = sizeof(double);
        DOUBLE_TYPEINFO.sum = sum_double;
        DOUBLE_TYPEINFO.mull = mull_double;
        DOUBLE_TYPEINFO.print_element = print_element_double;
    }
    return &DOUBLE_TYPEINFO;
}
