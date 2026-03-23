#include "bool_info.h"
#include <stdio.h>

// Выполняет логическое ИЛИ (сложение) для булевых элементов
static void sum_bool(const void* a, const void* b, void* out) {
    const int* a1 = (const int*)a;
    const int* b1 = (const int*)b;
    int* rez = (int*)out;
    
    *rez = (*a1) | (*b1); 
}

// Выполняет логическое И (умножение) для булевых элементов
static void mull_bool(const void* a, const void* b, void* out) {
    const int* x = (const int*)a;
    const int* y = (const int*)b;
    int* rez = (int*)out;
    
    *rez = (*x) & (*y); 
}

// Выводит булев элемент в стандартный поток вывода
static void print_element_bool(const void* elem) {
    int val = *(const int*)elem;
    
    if (val != 0) {
        printf("True");
    } else {
        printf("False");
    }
}

// Глобальные переменные для одиночки (singleton) информации о булевом типе
static TypeInfo BOOL_TYPEINFO;
int BOOL_INIT_TYPEINFO = 0;

// Инициализирует и возвращает структуру TypeInfo для булевых типов
const TypeInfo* GetBoolInfo(void) {
    if (BOOL_INIT_TYPEINFO != 1) {
        BOOL_INIT_TYPEINFO = 1;
        
        BOOL_TYPEINFO.size = sizeof(int);
        BOOL_TYPEINFO.sum = sum_bool;
        BOOL_TYPEINFO.mull = mull_bool;
        BOOL_TYPEINFO.print_element = print_element_bool;
    }
    
    return &BOOL_TYPEINFO;
}
