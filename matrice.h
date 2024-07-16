#ifndef matrice_h
#define matrice_h

#include <math.h>
#include <stddef.h>
#include <stdio.h>

#ifndef M_MALLOC
#include <stdlib.h>
#define M_MALLOC malloc
#endif //M_MALLOC

#ifndef M_ASSERT
#include <assert.h>
#define M_ASSERT assert
#endif //M_ASSERT

#define index(m, i, j) (m).element[(i)*(m).col+(j)]

typedef struct {
    int row;
    int col;
    float *element;
} Matrix;

float sigmoid_func(float sum);
Matrix mat_init(int row, int col);
void mat_rand(Matrix m);
void mat_fill(Matrix m, int x);
void mat_product(Matrix dest, Matrix m, Matrix n);
Matrix mat_row(Matrix m, int row);
void mat_copy(Matrix dest, Matrix src);
void mat_sum(Matrix dest, Matrix m);
void mat_sig(Matrix m);
void print_mat(Matrix m);

#endif //matrice_h

// #ifndef MATRICE_IMPL
#ifdef MATRICE_IMPL

Matrix mat_init(int row, int col) {
    Matrix m;
    m.row = row;
    m.col = col;
    m.element = (float *)M_MALLOC(sizeof(float) * row * col);
    M_ASSERT(m.element != NULL);
    return m;
}

void mat_rand(Matrix m) {
    for (int i = 0; i < m.row; i++) {
        for (int j = 0; j < m.col; j++) {
            index(m, i, j) = (float)rand()/RAND_MAX;
        }
    }
}

void mat_fill(Matrix m, int x) {
    for (int i = 0; i < m.row; i++) {
        for (int j = 0; j < m.col; j++) {
            index(m, i, j) = x;
        }
    }
}

void mat_product(Matrix dest, Matrix m, Matrix n) {
    M_ASSERT(m.col == n.row);
    M_ASSERT(dest.row == m.row);
    M_ASSERT(dest.col == n.col);

    float common = m.col;

    for (int i = 0; i < dest.row; i++) {
        for (int j = 0; j < dest.col; j++) {
            index(dest, i, j);
            for (int c = 0; c < common; c++) {
                index(dest, i, j) += index(m, i, c) * index(n, c, j);
            }
        }
    }
    
}

Matrix mat_row(Matrix m, int row) {
    return (Matrix) {
        .row = 1,
        .col = m.col,
        .element = &index(m, row, 0)
    };
}
void mat_copy(Matrix dest, Matrix src) {
    M_ASSERT(dest.row == src.row);
    M_ASSERT(dest.col == src.col);
    for (int i = 0; i < dest.row; i++) {
        for (int j = 0; j < dest.col; j++) {
            index(dest, i, j) = index(src, i, j);
        }
    }

}

void mat_sum(Matrix dest, Matrix m) {
    M_ASSERT(dest.row == m.row);
    M_ASSERT(dest.col == m.col);
    for (int i = 0; i < dest.row; i++) {
        for (int j = 0; j < dest.col; j++) {
            index(dest, i, j) += index(m, i, j);
        }
    }
}

float sigmoid_func(float sum) {
    return 1 / (1 + exp(-sum));
}

void mat_sig(Matrix m) {
    for (int i = 0; i < m.row; i++) {
        for (int j = 0; j < m.col; j++) {
            index(m, i, j) += sigmoid_func(index(m, i, j));
        }
    }
}

void print_mat(Matrix m) {
    for (int i = 0; i < m.row; i++) {
        for (int j = 0; j < m.col; j++) {
            printf("%f ", index(m, i, j));
        }
        printf("\n");
    }
}

#endif //matrice_impl
