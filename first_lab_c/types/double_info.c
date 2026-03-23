#include "double_info.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "data.h"

// Складывает два значения типа double и сохраняет результат в 'out'
static void sum_double(const void* a, const void* b, void* out){
    const double* a1 = (const double*)a;
    const double* b1 = (const double*)b;
    double* rez = (double*)out;
    
    *rez = *a1 + *b1;
}

// Умножает два значения типа double и сохраняет результат в 'out'
static void mull_double(const void* a, const void* b, void* out){
    const double* x = (const double*)a;
    const double* y = (const double*)b;
    double* rez = (double*)out;
    
    *rez = (*x) * (*y);
}

// Выводит значение типа double в стандартный поток вывода
static void print_element_double(const void* elem) {
    printf("%f", *(const double*)elem);
}

// Глобальные переменные для одиночки (singleton) информации о типе double
static TypeInfo DOUBLE_TYPEINFO;
int DOUBLE_INIT_TYPEINFO = 0;

// Инициализирует и возвращает структуру TypeInfo для типов double
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
