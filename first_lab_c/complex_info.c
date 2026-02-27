#include "complex_info.h"
#include <stdio.h>
#include <stdlib.h>
// реализация операций для complex
// + и * для complex
imagine complex_add(imagine a, imagine b){
    imagine result;
    result.re = a.re + b.re;
    result.im = a.im + b.im;
    return result;
}

imagine complex_mull(imagine a, imagine b){
    imagine result;
    result.re = a.re*b.re - a.im*b.im;
    result.im = a.re*b.im + b.re*a.im;
    return result;
}
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
//
static void plus_complex(const void* matrix1,const void* matrix2, void* rez){
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
    imagine* a = (imagine*)m1->matrix;
    imagine* b = (imagine*)m2->matrix;
    imagine* re = (imagine*)r->matrix;
    int cols = m1->cols;
    int rows = m1->rows;
    
    for (int ind = 0; ind < rows*cols; ind++){
        m1->typeinfo->sum((a + ind) , (b + ind), (re + ind));
    }
}

// произведение матриц
static void multiplication_complex(const void* matrix1,const void*matrix2, void* rez){
    const Matrix* m1 = (const Matrix*)matrix1;
    const Matrix* m2 = (const Matrix*)matrix2;
    Matrix* r = (Matrix*)rez;
    // проверка на передачу нам одинаковых форматов
    if (m1->typeinfo != m2->typeinfo) return;
    // проверка существования произведения матриц
    if (m1->cols != m2->rows) return;
    if (r->rows != m1->rows || r->cols != m2->cols) return;
    imagine* a = (imagine*)m1->matrix;
    imagine* b = (imagine*)m2->matrix;
    imagine* rez_matrix = (imagine*)r->matrix;
    
    int m = m1->rows;
    int n = m1->cols;
    int k = m2->cols;
    for (int i = 0; i < m*k; i++){
            rez_matrix[i].re = 0.0;
            rez_matrix[i].im = 0.0;
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < k; j++){
            imagine sum = {0.0, 0.0};
            for (int t = 0; t < n; t++){
                imagine prod;
                m1->typeinfo->mull(a + i*n + t, b + t*k + j, &prod);
                m1->typeinfo->plus(&sum, &prod, &sum);
            }
            *(rez_matrix + i*k + j) = sum;
        }
    }
}


// произведение на скаляр
static void scalar_multiplication_complex(const void* matrix1,const void* scalar, void* rez){
    const Matrix* m1 = (const Matrix*)matrix1;
    Matrix* r = (Matrix*)rez;
    const imagine* sc = (const imagine*)scalar;
    imagine* mat = (imagine*)m1->matrix;
    imagine* rez_matrix = (imagine*)r->matrix;
    int rows = m1->rows;
    int cols = m1->cols;
    // проверка на выход за границы
    if (r->rows != rows || r->cols != cols) return;
    for (int i = 0; i<rows*cols; i++){
        mull_complex(sc, mat + i, rez_matrix + i);
    }
}

// транспонирование complex
static void trasponation_complex(const void* matrix, void* rez){
    const Matrix* m = (const Matrix*)matrix;
    Matrix* r = (Matrix*)rez;
    imagine* mat = (imagine*)m->matrix;
    imagine* rez_matrix = (imagine*)r->matrix;
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
static Matrix* AddLinearCombination_complex(Matrix* matrix, int rowIndex, void* alphas){
    imagine* m1 = (imagine*)matrix->matrix;
    int cols = matrix->cols;
    int rows = matrix->rows;
    imagine* alph = (imagine*)alphas;
    int current_koof = 0;
    Matrix* rezult = matrix_create(GetComplexleInfo(), rows, cols);
    memcpy(rezult->matrix, m1, rows*cols*sizeof(imagine));
    imagine* rezult_matrix = rezult->matrix;
    for (int i = 0; i < cols; i++){
        current_koof = 0;
        for (int j = 0; j < rows; j++){
            if (j == rowIndex) continue;
            imagine prod;
            matrix->typeinfo->mull(rezult_matrix + cols*j + i, alph + current_koof, &prod);
            matrix->typeinfo->plus(rezult_matrix + cols*rowIndex + i, &prod, rezult_matrix + cols*rowIndex + i);
            ++current_koof;
        }
    }
    return rezult;
}

// печать complex

static void print_complex(const void* matrix, int el){
    const Matrix* m = (const Matrix*)matrix;
    const imagine* mat = (const imagine*)m->matrix;
    int rows = m->rows;
    int cols = m->cols;
    int total = rows * cols;

    if (el >= 0) {
        if (el >= total)return;
        printf("%f + %fi\n", mat[el].re, mat[el].im);
        return;
    }
    for (int i = 0; i < total; i++){
        printf("%f + %fi", mat[i].re, mat[i].im);
        printf(" ");
        if ((i+1) % cols == 0) printf("\n");
    }
}


// ленивая инициализация для complex
static TypeInfo COMPLEX_TYPEINFO;
int COMPLEX_INIT_TYPEINFO = 0;
TypeInfo* GetComplexleInfo(void){
    if (COMPLEX_INIT_TYPEINFO != 1){
        COMPLEX_INIT_TYPEINFO = 1;
        COMPLEX_TYPEINFO.size = sizeof(imagine);
        COMPLEX_TYPEINFO.sum = sum_complex;
        COMPLEX_TYPEINFO.mull = mull_complex;
        COMPLEX_TYPEINFO.plus = plus_complex;
        COMPLEX_TYPEINFO.multiplication = multiplication_complex;
        COMPLEX_TYPEINFO.scalar_multiplication = scalar_multiplication_complex;
        COMPLEX_TYPEINFO.transponation = trasponation_complex;
        COMPLEX_TYPEINFO.AddLinearCombination = AddLinearCombination_complex;
        COMPLEX_TYPEINFO.print = print_complex;
    }
    return &COMPLEX_TYPEINFO;
}



// +


