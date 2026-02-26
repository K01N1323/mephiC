/*#include "typeinfo.h"
#include <string.h>
// ленивая инициализация для int
//реализация операций для int
static void plus_int(const void* matrix1,const void* matrix2, void* rez){
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
    int* a = (int*)m1->matrix;
    int* b = (int*)m2->matrix;
    int* re = (int*)r->matrix;
    int cols = m1->cols;
    int rows = m1->rows;
    
    for (int ind = 0; ind < rows*cols; ind++){
        *(re + ind) = *(a + ind) + *(b + ind);
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
                int a_ij = *(a + i*n + t);
                int b_ij = *(b + t*k + j);
                sum += a_ij * b_ij;
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
        *(rez_matrix + i) = *(mat + i) * (*sc);
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
//  m1[cols*rowIndex + index] +=
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
            rezult_matrix[cols*rowIndex + i] += rezult_matrix[cols*j + i] * alph[current_koof];
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
    for (int i=0; i < cols*rows; i++){
        printf("%d", mat[i]);
        printf("    ");
        if (i==el) break;
        if ((i+1) % cols == 0) printf("\n");
    }
}

// реализация для double
static void plus_double(const void* matrix1,const void* matrix2, void* rez){
    const Matrix* m1 = (const Matrix*)matrix1;
    const Matrix* m2 = (const Matrix*)matrix2;
    Matrix* r        = (Matrix*)rez;
    // проверка на передачу нам одинаковых форматов
    if (m1->typeinfo != m2->typeinfo) return;
    // проверки на неправильные форматы
    if (m1->rows!=m2->rows || m1->cols!=m2->cols) {
        return;
    }
    if (r->rows!=m1->rows || r->cols!=m1->cols) {
        return;
    }
    double* a  = (double*)m1->matrix;
    double* b  = (double*)m2->matrix;
    double* re = (double*)r->matrix;
    int cols = m1->cols;
    int rows = m1->rows;

    for (int ind = 0; ind < rows*cols; ind++){
        *(re + ind) = *(a + ind) + *(b + ind);
    }
}


// произведение матриц
static void multiplication_double(const void* matrix1,const void*matrix2, void* rez){
    const Matrix* m1 = (const Matrix*)matrix1;
    const Matrix* m2 = (const Matrix*)matrix2;
    Matrix* r        = (Matrix*)rez;
    // проверка на передачу нам одинаковых форматов
    if (m1->typeinfo != m2->typeinfo) return;
    // проверка существования произведения матриц
    if (m1->cols != m2->rows) return;
    if (r->rows != m1->rows || r->cols != m2->cols) return;
    double* a  = (double*)m1->matrix;
    double* b  = (double*)m2->matrix;
    double* rez_matrix= (double*)r->matrix;

    int m = m1->rows;
    int n = m1->cols;
    int k = m2->cols;
    for (int i = 0; i < m*k; i++){
        *(rez_matrix + i) = 0.0;
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < k; j++){
            double sum = 0.0;
            for (int t = 0; t < n; t++){
                double a_ij = *(a + i*n + t);
                double b_ij = *(b + t*k + j);
                sum += a_ij * b_ij;
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
    for (int i = 0; i<rows*cols; i++){
        *(rez_matrix + i) = *(mat + i) * (*sc);
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
    double* rezult_matrix = rezult->matrix;
    for (int i = 0; i < cols; i++){
        current_koof = 0;
        for (int j = 0; j < rows; j++){
            if (j == rowIndex) continue;
            rezult_matrix[cols*rowIndex + i] += rezult_matrix[cols*j + i] * alph[current_koof];
            ++current_koof;
        }
    }
    return rezult;
}

static void print_double(const void* matrix, int el){
    const Matrix* m = (const Matrix*)matrix;
    const double* mat = (const double*)m->matrix;
    int rows = m->rows;
    int cols = m->cols;
    for (int i=0; i < cols*rows; i++){
        printf("%f", mat[i]);
        printf("    ");
        if (i == el) break;
        if ((i+1) % cols == 0) printf("\n");
    }
}


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
        *(re + ind) = complex_add(*(a + ind) , *(b + ind));
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
                imagine a_ij = *(a + i*n + t);
                imagine b_ij = *(b + t*k + j);
                sum = complex_add(sum, complex_mull(a_ij, b_ij));
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
        rez_matrix[i] = complex_mull(mat[i], *sc);
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
            rezult_matrix[cols*rowIndex + i] = complex_add(rezult_matrix[cols*rowIndex + i], complex_mull( rezult_matrix[cols*j + i] , alph[current_koof]));
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
    for (int i=0; i < cols*rows; i++){
        printf("%f", mat[i].re);
        printf(" + ");
        printf("%f", mat[i].im);
        printf("i");
        printf("    ");
        if (i == el) break;
        if ((i+1) % cols == 0) printf("\n");
    }
}

// +








static TypeInfo INT_TYPEINFO;
int INT_INIT_TYPEINFO = 0;
TypeInfo* GetIntInfo(void){
    if (INT_INIT_TYPEINFO != 1){
        INT_INIT_TYPEINFO = 1;
        INT_TYPEINFO.size = sizeof(int);
        INT_TYPEINFO.plus = plus_int;
        INT_TYPEINFO.multiplication = multiplication_int;
        INT_TYPEINFO.scalar_multiplication = scalar_multiplication_int;
        INT_TYPEINFO.transponation = trasponation_int;
        INT_TYPEINFO.AddLinearCombination = AddLinearCombination_int;
        INT_TYPEINFO.print = print_int;
    }
    return &INT_TYPEINFO;
}
// ленивая инициализация для double
static TypeInfo DOUBLE_TYPEINFO;
int DOUBLE_INIT_TYPEINFO = 0;
TypeInfo* GetDoubleInfo(void){
    if (DOUBLE_INIT_TYPEINFO != 1){
        DOUBLE_INIT_TYPEINFO = 1;
        DOUBLE_TYPEINFO.size = sizeof(double);
        DOUBLE_TYPEINFO.plus = plus_int;
        DOUBLE_TYPEINFO.multiplication = multiplication_int;
        DOUBLE_TYPEINFO.scalar_multiplication = scalar_multiplication_int;
        DOUBLE_TYPEINFO.transponation = trasponation_double;
        DOUBLE_TYPEINFO.AddLinearCombination = AddLinearCombination_double;
        DOUBLE_TYPEINFO.print = print_double;
    }
    return &DOUBLE_TYPEINFO;
}
// ленивая инициализация для complex
static TypeInfo COMPLEX_TYPEINFO;
int COMPLEX_INIT_TYPEINFO = 0;
TypeInfo* GetComplexleInfo(void){
    if (COMPLEX_INIT_TYPEINFO != 1){
        COMPLEX_INIT_TYPEINFO = 1;
        COMPLEX_TYPEINFO.size = sizeof(imagine);
        COMPLEX_TYPEINFO.plus = plus_int;
        COMPLEX_TYPEINFO.multiplication = multiplication_int;
        COMPLEX_TYPEINFO.scalar_multiplication = scalar_multiplication_int;
        COMPLEX_TYPEINFO.transponation = trasponation_complex;
        COMPLEX_TYPEINFO.AddLinearCombination = AddLinearCombination_complex;
        COMPLEX_TYPEINFO.print = print_complex;
    }
    return &COMPLEX_TYPEINFO;
}*/


