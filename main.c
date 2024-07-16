#include <stdio.h>
#include <time.h>
#define MATRICE_IMPL
#include "matrice.h"

typedef int sample[3];
typedef struct {
    Matrix a0;

    Matrix w1;
    Matrix b1;
    Matrix a1;

    Matrix w2;
    Matrix b2;
    Matrix a2;
} Modle ;

sample xor_train[] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0},
};

sample *train = xor_train;
int train_size = 4;

Modle initializer() {
    Modle m;

    m.a0 = mat_init(1, 2);

    m.w1 = mat_init(2, 2);
    m.b1 = mat_init(1, 2);
    m.a1 = mat_init(1, 2);

    m.w2 = mat_init(2, 1);
    m.b2 = mat_init(1, 1);
    m.a2 = mat_init(1, 1);

    return m;
}

void forward(Modle m) {
    mat_rand(m.w1);
    mat_rand(m.b1);
    mat_rand(m.w2);
    mat_rand(m.b2);

    mat_product(m.a1, m.a0, m.w1);
    mat_sum(m.a1, m.b1);
    mat_sig(m.a1);

    mat_product(m.a2, m.a1, m.w2);
    mat_sum(m.a2, m.b2);
    mat_sig(m.a2);
}

float cost(Modle m, Matrix in, Matrix expected) {
    assert(in.row == expected.row);
    assert(m.a2.col == expected.col);
    int n = in.row;

    float sum = 0;
    for (int i = 0; i < n; i++) {
        Matrix x = mat_row(in, i);
        Matrix y = mat_row(expected, i);

        mat_copy(m.a0, x);
        forward(m);

        for (int j = 0; j < expected.col; j++) {
            float error  = index(m.a2, 0, j) - index(y, 0, j);
            sum += error * error;
        }
    }
    return sum / n;
}

int main() {
    srand(time(0));
    Modle m = initializer();


    return 0;
}
