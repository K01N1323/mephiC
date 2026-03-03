#include "complex_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

static void sum_complex(const void* a, const void* b, void* out){
    const imagine* a1 = (const imagine*)a;
    const imagine* b1 = (const imagine*)b;
    imagine* rez = (imagine*)out;
    rez->re = a1->re + b1->re;
    rez->im = a1->im + b1->im;
}

static void mull_complex(const void* a,const void* b, void* out){
    const imagine* a1 = (const imagine*)a;
    const imagine* b1 = (const imagine*)b;
    imagine* rez = (imagine*)out;
    rez->re = a1->re * b1->re - a1->im * b1->im;
    rez->im = a1->im * b1->re + a1->re * b1->im;
}

static void print_element_complex(const void* elem) {
    const imagine* cmp = (const imagine*)elem;
    printf("%f + %fi", cmp->re, cmp->im);
}

static TypeInfo COMPLEX_TYPEINFO;
int COMPLEX_INIT_TYPEINFO = 0;
const TypeInfo* GetComplexleInfo(void){
    if (COMPLEX_INIT_TYPEINFO != 1){
        COMPLEX_INIT_TYPEINFO = 1;
        COMPLEX_TYPEINFO.size = sizeof(imagine);
        COMPLEX_TYPEINFO.sum = sum_complex;
        COMPLEX_TYPEINFO.mull = mull_complex;
        COMPLEX_TYPEINFO.print_element = print_element_complex;
    }
    return &COMPLEX_TYPEINFO;
}
