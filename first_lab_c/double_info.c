#include "double_info.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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

// реализация для double
static void plus_double(const void* matrix1,const void* matrix2, void* rez){
    const Matrix* m1 = (const Matrix*)matrix1;
    const Matrix* m2 = (const Matrix*)matrix2;
    const Matrix* r = (const Matrix*)rez;
    // проверка на передачу нам одинаковых форматов
    if (m1->typeinfo != m2->typeinfo) return;
    // проверки на неправильные форматы
    if (m1->rows!=m2->rows || m1->cols!=m2->cols) {
        return;
    }
    if (r->rows!=m1->rows || r->cols!=m1->cols) {
        return;
    }
    double* a = (double*)m1->matrix;
    double* b = (double*)m2->matrix;
    double* re = (double*)r->matrix;
    int cols = m1->cols;
    int rows = m1->rows;
    
    for (int ind = 0; ind < rows*cols; ind++){
        m1->typeinfo->sum(a + ind, b + ind, re + ind);
    }
}

// произведение матриц
static void multiplication_double(const void* matrix1,const void*matrix2, void* rez){
    const Matrix* m1 = (const Matrix*)matrix1;
    const Matrix* m2 = (const Matrix*)matrix2;
    Matrix* r = (Matrix*)rez;
    // проверка на передачу нам одинаковых форматов
    if (m1->typeinfo != m2->typeinfo) return;
    // проверка существования произведения матриц
    if (m1->cols != m2->rows) return;
    if (r->rows != m1->rows || r->cols != m2->cols) return;
    double* a = (double*)m1->matrix;
    double* b = (double*)m2->matrix;
    double* rez_matrix = (double*)r->matrix;
    
    int m = m1->rows;
    int n = m1->cols;
    int k = m2->cols;
    for (int i = 0; i < m*k; i++){
        rez_matrix[i] = 0.0;
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < k; j++){
            double sum = 0.0;
            for (int t = 0; t < n; t++){
                double prod;
                m1->typeinfo->mull(a + i*n + t, b + t*k + j, &prod);
                m1->typeinfo->sum(&sum, &prod, &sum);
            }
            *(rez_matrix + i*k + j) = sum;
        }
    }
}

// произведение на скаляр
static void scalar_multiplication_double(const void* matrix1,const void* scalar, void* rez){
    const Matrix* m1 = (const Matrix*)matrix1;
    Matrix* r = (Matrix*)rez;
    const double* sc = (const double*)scalar;
    double* mat = (double*)m1->matrix;
    double* rez_matrix = (double*)r->matrix;
    int rows = m1->rows;
    int cols = m1->cols;
    // проверка на выход за границы
    if (r->rows != rows || r->cols != cols) return;
    for (int i = 0; i < rows*cols; i++){
        m1->typeinfo->mull(mat + i, sc, rez_matrix + i);
    }
}

// транспонирование double
static void trasponation_double(const void* matrix, void* rez){
    const Matrix* m = (const Matrix*)matrix;
    Matrix* r = (Matrix*)rez;
    double* mat = (double*)m->matrix;
    double* rez_matrix = (double*)r->matrix;
    int rows = m->rows;
    int cols = m->cols;
    if (r->rows != cols || r->cols != rows) return;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            *(rez_matrix + rows*j + i) = *(mat + cols*i + j);
        }
    }
}

// линейная комбинация
static Matrix* AddLinearCombination_double(Matrix* matrix, int rowIndex, void* alphas){
    double* m1 = (double*)matrix->matrix;
    int cols = matrix->cols;
    int rows = matrix->rows;
    double* alph = (double*)alphas;
    int current_koof = 0;
    Matrix* rezult = matrix_create(GetDoubleInfo(), rows, cols);
    memcpy(rezult->matrix, m1, rows*cols*sizeof(double));
    double* rezult_matrix = (double*)rezult->matrix;
    for (int i = 0; i < cols; i++){
        current_koof = 0;
        for (int j = 0; j < rows; j++){
            if (j == rowIndex) continue;
            double prod;
            matrix->typeinfo->mull(&rezult_matrix[cols*j + i], &alph[current_koof], &prod);
            matrix->typeinfo->sum(&rezult_matrix[cols*rowIndex + i], &prod, &rezult_matrix[cols*rowIndex + i]);
            ++current_koof;
        }
    }
    return rezult;
}

// печать double матрицы
static void print_double(const void* matrix, int el){
    const Matrix* m = (const Matrix*)matrix;
    const double* mat = (const double*)m->matrix;
    int rows = m->rows;
    int cols = m->cols;
    int total = rows * cols;
    if (el >= 0) return;
    for (int i = 0; i < total; i++){
        printf("%f", mat[i]);
        printf(" ");
        if ((i+1) % cols == 0) printf("\n");
    }
}

// ленивая инициализация для double
static TypeInfo DOUBLE_TYPEINFO;
int DOUBLE_INIT_TYPEINFO = 0;
TypeInfo* GetDoubleInfo(void){
    if (DOUBLE_INIT_TYPEINFO != 1){
        DOUBLE_INIT_TYPEINFO = 1;
        DOUBLE_TYPEINFO.size = sizeof(double);
        DOUBLE_TYPEINFO.sum = sum_double;
        DOUBLE_TYPEINFO.mull = mull_double;
        DOUBLE_TYPEINFO.plus = plus_double;
        DOUBLE_TYPEINFO.multiplication = multiplication_double;
        DOUBLE_TYPEINFO.scalar_multiplication = scalar_multiplication_double;
        DOUBLE_TYPEINFO.transponation = trasponation_double;
        DOUBLE_TYPEINFO.AddLinearCombination = AddLinearCombination_double;
        DOUBLE_TYPEINFO.print = print_double;
    }
    return &DOUBLE_TYPEINFO;
}

