#include "int_info.h"
#include <string.h>
#include <stdio.h>
#include "data.h"

// Складывает два целых числа и сохраняет результат в 'out'
static void sum_int(const void* a, const void* b, void* out){
    const int* a1 = (const int*)a;
    const int* b1 = (const int*)b;
    int* rez = (int*)out;
    
    *rez = *a1 + *b1;
}

// Умножает два целых числа и сохраняет результат в 'out'
static void mull_int(const void* a, const void* b, void* out) {
    const int* x = (const int*)a;
    const int* y = (const int*)b;
    int* rez = (int*)out;
    
    *rez = *x * *y;
}

// Выводит целое число в стандартный поток вывода
static void print_element_int(const void* elem) {
    printf("%d", *(const int*)elem);
}

// Глобальные переменные для одиночки (singleton) информации о целочисленном типе
static TypeInfo INT_TYPEINFO;
int INT_INIT_TYPEINFO = 0;

// Инициализирует и возвращает структуру TypeInfo для целочисленных типов
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
