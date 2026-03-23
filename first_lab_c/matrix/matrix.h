#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "typeinfo.h"

// Структура матрицы (хранение данных одномерным массивом, доступ через cols*i + j)
struct Matrix {
    const TypeInfo* typeinfo; // Указатель на информацию о типе данных матрицы
    void* matrix;             // Указатель на сырые данные матрицы
    int rows;                 // Количество строк
    int cols;                 // Количество столбцов

    // Указатели на функции для операций над матрицей
    void (*plus)(const void* matrix1, const void* matrix2, void* rez);
    void (*multiplication)(const void* matrix1, const void* matrix2, void* rez);
    void (*scalar_multiplication)(const void* matrix1, const void* scalar, void* rez);
    void (*transponation)(const void* matrix, void* rez);
    Matrix* (*add_linear_combination)(Matrix* matrix, int rowIndex, void* alphas);
    void (*print)(const void* matrix, int el);
};

#endif // structures.h
