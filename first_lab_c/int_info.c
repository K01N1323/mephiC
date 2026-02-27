#include "int_info.h"
#include <string.h>
#include <stdio.h>
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
static void plus_int(const void* matrix1,const void* matrix2, void* rez){
    const Matrix* m1 = (const Matrix*)matrix1;
    const Matrix* m2 = (const Matrix*)matrix2;
    const Matrix* r = (const Matrix*)rez;
    // проверка на передачу нам одинаковых форматов
    if (m1->typeinfo != m2->typeinfo) return;
    // проверки на неправильные формы матрмц
    if (m1->rows!=m2->rows || m1->cols!=m2->cols) {
           return;
       }
    if (r->rows!=m1->rows || r->cols!=m1->cols) {
        return;
    }
    int* a = (int*)m1->matrix;
    int* b = (int*)m2->matrix;
    int* re = (int*)r->matrix;
    int cols = m1->cols;
    int rows = m1->rows;
    
    for (int ind = 0; ind < rows*cols; ind++){
        m1->typeinfo->sum(a + ind, b + ind, re + ind);
    }
}

// произведение матриц
static void multiplication_int(const void* matrix1,const void*matrix2, void* rez){
    const Matrix* m1 = (const Matrix*)matrix1;
    const Matrix* m2 = (const Matrix*)matrix2;
    Matrix* r = (Matrix*)rez;
    // проверка на передачу нам одинаковых форматов
    if (m1->typeinfo != m2->typeinfo) return;
    // проверка существования произведения матриц
    if (m1->cols != m2->rows) return;
    if (r->rows != m1->rows || r->cols != m2->cols) return;
    int* a = (int*)m1->matrix;
    int* b = (int*)m2->matrix;
    int* rez_matrix = (int*)r->matrix;
    
    int m = m1->rows;
    int n = m1->cols;
    int k = m2->cols;
    for (int i = 0; i < m*k; i++){
        rez_matrix[i] = 0;
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < k; j++){
            int sum = 0;
            for (int t = 0; t < n; t++){
                int prod;
                m1->typeinfo->mull(a + i*n + t, b + t*k + j, &prod);
                m1->typeinfo->sum(&sum, &prod, &sum);
            }
            *(rez_matrix + i*k + j) = sum;
        }
    }
}


// произведение на скаляр
static void scalar_multiplication_int(const void* matrix1,const void* scalar, void* rez){
    const Matrix* m1 = (const Matrix*)matrix1;
    Matrix* r = (Matrix*)rez;
    const int* sc = (const int*)scalar;
    int* mat = (int*)m1->matrix;
    int* rez_matrix = (int*)r->matrix;
    int rows = m1->rows;
    int cols = m1->cols;
    // проверка на выход за границы
    if (r->rows != rows || r->cols != cols) return;
    for (int i = 0; i<rows*cols; i++){
        m1->typeinfo->mull(mat + i, sc, rez_matrix + i);
    }
}

// транспонирование int
static void trasponation_int(const void* matrix, void* rez){
    const Matrix* m = (const Matrix*)matrix;
    Matrix* r = (Matrix*)rez;
    int* mat = (int*)m->matrix;
    int* rez_matrix = (int*)r->matrix;
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
static Matrix* AddLinearCombination_int(Matrix* matrix, int rowIndex, void* alphas){
    int* m1 = (int*)matrix->matrix;
    int cols = matrix->cols;
    int rows = matrix->rows;
    int* alph = (int*)alphas;
    int current_koof = 0;
    Matrix* rezult = matrix_create(GetIntInfo(), rows, cols);
    memcpy(rezult->matrix, m1, rows*cols*sizeof(int));
    int* rezult_matrix = rezult->matrix;
    for (int i = 0; i < cols; i++){
        current_koof = 0;
        for (int j = 0; j < rows; j++){
            if (j == rowIndex) continue;
            int prod;
            matrix->typeinfo->mull(&rezult_matrix[cols*j + i], &alph[current_koof], &prod);
            matrix->typeinfo->sum(&rezult_matrix[cols*rowIndex + i], &prod, &rezult_matrix[cols*rowIndex + i]);
            ++current_koof;
        }
    }
    return rezult;
}
// печать интовой матрицы
static void print_int(const void* matrix, int el){
    const Matrix* m = (const Matrix*)matrix;
    const int* mat = (const int*)m->matrix;
    int rows = m->rows;
    int cols = m->cols;
    int total = rows * cols;
    if (el >= 0) {
        if (el >= total) return;
        printf("%d\n", mat[el]);
        return;
    }
    for (int i = 0; i < total; i++){
        printf("%d", mat[i]);
        printf(" ");
        if ((i+1) % cols == 0) printf("\n");
    }
}


static TypeInfo INT_TYPEINFO;
int INT_INIT_TYPEINFO = 0;
TypeInfo* GetIntInfo(void){
    if (INT_INIT_TYPEINFO != 1){
        INT_INIT_TYPEINFO = 1;
        INT_TYPEINFO.size = sizeof(int);
        INT_TYPEINFO.sum = sum_int;
        INT_TYPEINFO.mull = mull_int;
        INT_TYPEINFO.plus = plus_int;
        INT_TYPEINFO.multiplication = multiplication_int;
        INT_TYPEINFO.scalar_multiplication = scalar_multiplication_int;
        INT_TYPEINFO.transponation = trasponation_int;
        INT_TYPEINFO.AddLinearCombination = AddLinearCombination_int;
        INT_TYPEINFO.print = print_int;
    }
    return &INT_TYPEINFO;
}
