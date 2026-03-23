#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "matrix.h"

// Универсальная функция сложения двух матриц
void generic_plus(const void* matrix1, const void* matrix2, void* rez);

// Универсальная функция умножения двух матриц
void generic_multiplication(const void* matrix1, const void* matrix2, void* rez);

// Универсальная функция умножения матрицы на скаляр
void generic_scalar_multiplication(const void* matrix1, const void* scalar, void* rez);

// Универсальная функция транспонирования матрицы
void generic_transponation(const void* matrix, void* rez);

// Универсальная функция прибавления к строке линейной комбинации других строк
Matrix* generic_add_linear_combination(Matrix* matrix, int rowIndex, void* alphas);

// Универсальная функция вывода матрицы на экран
void generic_print(const void* matrix, int el);

#endif // MATRIX_OPERATIONS_H
