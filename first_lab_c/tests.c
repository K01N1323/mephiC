#include "tests.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "data.h"
#include "int_info.h"
#include "double_info.h"
#include "complex_info.h"
#include "tests.h"


static int eq_int_array(const int* a, const int* b, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

static int eq_double_array(const double* a, const double* b, int n, double eps) {
    for (int i = 0; i < n; i++) {
        if (fabs(a[i] - b[i]) > eps) return 0;
    }
    return 1;
}

static int eq_complex_array(const imagine* a, const imagine* b, int n, double eps) {
    for (int i = 0; i < n; i++) {
        if (fabs(a[i].re - b[i].re) > eps) return 0;
        if (fabs(a[i].im - b[i].im) > eps) return 0;
    }
    return 1;
}

// генераторы данных
static void gen_int_positive(int* buf, int n) {
    for (int i = 0; i < n; i++) {
        int idx = i + 1;
        buf[i] = idx;
    }
}

static void gen_int_negative(int* buf, int n) {
    for (int i = 0; i < n; i++) {
        int idx = i + 1;
        buf[i] = -idx;
    }
}

static void gen_int_even_odd(int* buf, int n) {
    for (int i = 0; i < n; i++) {
        int idx = i + 1;
        int elem;
        if (idx % 2 == 0) {
            elem = idx;
        } else {
            elem = -idx;
        }
        buf[i] = elem;
    }
}

static void gen_int_mixed(int* buf, int n) {
    int half = n / 2;
    for (int i = 0; i < n; i++) {
        int idx = i + 1;
        int elem;
        if (idx <= half) {
            elem = -(half - idx + 1);
        } else {
            elem = idx - half;
        }
        buf[i] = elem;
    }
}

static void gen_double_positive(double* buf, int n) {
    for (int i = 0; i < n; i++) {
        int idx = i + 1;
        buf[i] = (double)idx / (double)(idx + 1);
    }
}

static void gen_double_negative(double* buf, int n) {
    for (int i = 0; i < n; i++) {
        int idx = i + 1;
        buf[i] = -(double)idx;
    }
}

static void gen_double_even_odd(double* buf, int n) {
    for (int i = 0; i < n; i++) {
        int idx = i + 1;
        double elem;
        if (idx % 2 == 0) {
            elem = (double)idx;
        } else {
            elem = (double)(-idx);
        }
        buf[i] = elem;
    }
}

static void gen_double_mixed(double* buf, int n) {
    int half = n / 2;
    for (int i = 0; i < n; i++) {
        int idx = i + 1;   // 1..n
        double elem;
        if (idx <= half) {
            elem = -(double)(half - idx + 1);
        } else {
            elem = (double)(idx - half);
        }
        buf[i] = elem;
    }
}


static void gen_complex_basic(imagine* buf, int n) {
    for (int i = 0; i < n; i++) {
        int idx = i + 1;
        buf[i].re = (double)idx;
        buf[i].im = (double)(-idx);
    }
}

// тесты для int
static void test_int_plus_positive_negative(void) {
    printf("НАЧАЛО test_int_plus_positive_negative\n");

    const TypeInfo* t = GetIntInfo();
    int rows = 2, cols = 3;
    int total = rows * cols;

    Matrix* a = matrix_create(t, rows, cols);
    Matrix* b = matrix_create(t, rows, cols);
    Matrix* c = matrix_create(t, rows, cols);

    int da[6];
    int db[6];
    int expected[6];
    int result[6];

    gen_int_positive(da, total);
    gen_int_negative(db, total);

    for (int i = 0; i < total; i++) {
        expected[i] = da[i] + db[i];
    }

    matrix_setall(a, da);
    matrix_setall(b, db);

    a->plus(a, b, c);
    matrix_getall(c, result);

    assert(eq_int_array(result, expected, total));

    matrix_free(a);
    matrix_free(b);
    matrix_free(c);

    printf("test_int_plus_positive_negative ПРОЙДЕН\n");
}

static void test_int_multiplication_even_odd(void) {
    printf("НАЧАЛО test_int_multiplication_even_odd\n");

    const TypeInfo* t = GetIntInfo();
    int rows = 2, cols = 2;
    int total = rows * cols;

    Matrix* a = matrix_create(t, rows, cols);
    Matrix* b = matrix_create(t, rows, cols);
    Matrix* c = matrix_create(t, rows, cols);

    int da[4];
    int db[4];
    int expected[4];
    int result[4];

    gen_int_even_odd(da, total);
    gen_int_mixed(db, total);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int sum = 0;
            for (int k = 0; k < cols; k++) {
                int a_ik = da[i*cols + k];
                int b_kj = db[k*cols + j];
                sum += a_ik * b_kj;
            }
            expected[i*cols + j] = sum;
        }
    }

    matrix_setall(a, da);
    matrix_setall(b, db);

    a->multiplication(a, b, c);
    matrix_getall(c, result);

    assert(eq_int_array(result, expected, total));

    matrix_free(a);
    matrix_free(b);
    matrix_free(c);

    printf("test_int_multiplication_even_odd ПРОЙДЕН\n");
}

static void test_int_scalar_mixed(void) {
    printf("НАЧАЛО test_int_scalar_mixed\n");

    const TypeInfo* t = GetIntInfo();
    int rows = 3, cols = 3;
    int total = rows * cols;

    Matrix* a = matrix_create(t, rows, cols);
    Matrix* c = matrix_create(t, rows, cols);

    int da[9];
    int expected[9];
    int result[9];
    int sc = -2;

    gen_int_mixed(da, total);

    for (int i = 0; i < total; i++) {
        expected[i] = da[i] * sc;
    }

    matrix_setall(a, da);
    a->scalar_multiplication(a, &sc, c);
    matrix_getall(c, result);

    assert(eq_int_array(result, expected, total));

    matrix_free(a);
    matrix_free(c);

    printf("test_int_scalar_mixed ПРОЙДЕН\n");
}

static void test_int_transpose_positive(void) {
    printf("НАЧАЛО test_int_transpose_positive\n");

    const TypeInfo* t = GetIntInfo();
    int rows = 2, cols = 3;
    int total = rows * cols;

    Matrix* a  = matrix_create(t, rows, cols);
    Matrix* tr = matrix_create(t, cols, rows);

    int da[6];
    int expected[6];
    int result[6];

    gen_int_positive(da, total);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int val = da[i*cols + j];
            expected[j*rows + i] = val;
        }
    }

    matrix_setall(a, da);
    a->transponation(a, tr);
    matrix_getall(tr, result);

    assert(eq_int_array(result, expected, total));

    matrix_free(a);
    matrix_free(tr);

    printf("test_int_transpose_positive ПРОЙДЕН\n");
}

// тесты для double
static void test_double_plus_positive_negative(void) {
    printf("НАЧАЛО test_double_plus_positive_negative\n");

    const TypeInfo* t = GetDoubleInfo();
    int rows = 2, cols = 3;
    int total = rows * cols;

    Matrix* a = matrix_create(t, rows, cols);
    Matrix* b = matrix_create(t, rows, cols);
    Matrix* c = matrix_create(t, rows, cols);

    double da[6];
    double db[6];
    double expected[6];
    double result[6];

    gen_double_positive(da, total);
    gen_double_negative(db, total);

    for (int i = 0; i < total; i++) {
        expected[i] = da[i] + db[i];
    }

    matrix_setall(a, da);
    matrix_setall(b, db);
    a->plus(a, b, c);
    matrix_getall(c, result);

    assert(eq_double_array(result, expected, total, 1e-9));

    matrix_free(a);
    matrix_free(b);
    matrix_free(c);

    printf("test_double_plus_positive_negative ПРОЙДЕН\n");
}

static void test_double_multiplication_even_odd(void) {
    printf("НАЧАЛО test_double_multiplication_even_odd\n");

    const TypeInfo* t = GetDoubleInfo();
    int rows = 2, cols = 2;
    int total = rows * cols;

    Matrix* a = matrix_create(t, rows, cols);
    Matrix* b = matrix_create(t, rows, cols);
    Matrix* c = matrix_create(t, rows, cols);

    double da[4];
    double db[4];
    double expected[4];
    double result[4];

    gen_double_even_odd(da, total);
    gen_double_mixed(db, total);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < cols; k++) {
                double a_ik = da[i*cols + k];
                double b_kj = db[k*cols + j];
                sum += a_ik * b_kj;
            }
            expected[i*cols + j] = sum;
        }
    }

    matrix_setall(a, da);
    matrix_setall(b, db);
    a->multiplication(a, b, c);
    matrix_getall(c, result);

    assert(eq_double_array(result, expected, total, 1e-9));

    matrix_free(a);
    matrix_free(b);
    matrix_free(c);

    printf("test_double_multiplication_even_odd ПРОЙДЕН\n");
}

// тесты для complex
static void test_complex_plus_basic(void) {
    printf("НАЧАЛО test_complex_plus_basic\n");

    const TypeInfo* t = GetComplexleInfo();
    int rows = 2, cols = 2;
    int total = rows * cols;

    Matrix* a = matrix_create(t, rows, cols);
    Matrix* b = matrix_create(t, rows, cols);
    Matrix* c = matrix_create(t, rows, cols);

    imagine da[4];
    imagine db[4];
    imagine expected[4];
    imagine result[4];

    gen_complex_basic(da, total);
    gen_complex_basic(db, total);

    for (int i = 0; i < total; i++) {
        expected[i].re = da[i].re + db[i].re;
        expected[i].im = da[i].im + db[i].im;
    }

    matrix_setall(a, da);
    matrix_setall(b, db);
    a->plus(a, b, c);
    matrix_getall(c, result);

    assert(eq_complex_array(result, expected, total, 1e-9));

    matrix_free(a);
    matrix_free(b);
    matrix_free(c);

    printf("test_complex_plus_basic ПРОЙДЕН\n");
}

void start_auto_tests(void) {
    printf("ЗАПУСК АВТОТЕСТОВ МАТРИЦ\n");

    // int
    test_int_plus_positive_negative();
    test_int_multiplication_even_odd();
    test_int_scalar_mixed();
    test_int_transpose_positive();

    // double
    test_double_plus_positive_negative();
    test_double_multiplication_even_odd();

    // complex
    test_complex_plus_basic();

    printf("ВСЕ ТЕСТЫ МАТРИЦ ПРОЙДЕНЫ \n");
}

