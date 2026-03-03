#ifndef TYPEINFO_H
#define TYPEINFO_H
#include "matrix.h"
#include <stddef.h>
typedef struct Matrix Matrix;
typedef struct{
    size_t size;
    void (*sum)(const void* a, const void* b, void* out);
    void (*mull)(const void* a, const void* b, void* out);
    void (*print_element)(const void* elem);
}TypeInfo;
#endif //typeinfo.h
// перенести функции в структуру Matrix
// геттеры инфы о данных const
// функция печати элемента одна для всеъ типов данных
// она вызывает печать из себя всей матрицы
