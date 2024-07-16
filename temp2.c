#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int sample[3];
typedef struct {
    float or_w1;
    float or_w2;
    float or_b;
    float nand_w1;
    float nand_w2;
    float nand_b;
    float and_w1;
    float and_w2;
    float and_b;
} Xor ;

sample xor_train[] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0},
};

sample *train = xor_train;
int train_size = 4;

float sigmoid_func(float sum) {
    return 1 / (1 + exp(-sum));
}

float forward(Xor m, float x1, float x2) {
    float or = sigmoid_func(x1 * m.or_w1 + x2 * m.or_w2 + m.or_b);
    float nand = sigmoid_func(x1 * m.nand_w1 + x2 * m.nand_w2 + m.nand_b);
    return sigmoid_func(or * m.and_w1 + nand * m.and_w2 + m.and_b);
}

float cost(Xor m) {
    float sum = 0;
    for (int i = 0; i < train_size; i++) {
        float input1 = train[i][0];
        float input2 = train[i][1];
        float output = train[i][2];
        float prediction = forward(m, input1, input2);
        float error = prediction - output;
        sum += error * error;
    }
    sum /= (float) train_size;

    return sum;
}

Xor finite_difference(Xor m, float eps) {
    Xor temp_modle;
    float temp;

    float c = cost(m);

    temp = m.or_w1;
    m.or_w1 += eps;
    temp_modle.or_w1 = (cost(m) - c)/eps;
    m.or_w1 = temp;

    temp = m.or_w2;
    m.or_w2 += eps;
    temp_modle.or_w2 = (cost(m) - c)/eps;
    m.or_w2 = temp;

    temp = m.or_b;
    m.or_b += eps;
    temp_modle.or_b = (cost(m) - c)/eps;
    m.or_b = temp;

    temp = m.nand_w1;
    m.nand_w1 += eps;
    temp_modle.nand_w1 = (cost(m) - c)/eps;
    m.nand_w1 = temp;

    temp = m.nand_w2;
    m.nand_w2 += eps;
    temp_modle.nand_w2 = (cost(m) - c)/eps;
    m.nand_w2 = temp;

    temp = m.nand_b;
    m.nand_b += eps;
    temp_modle.nand_b = (cost(m) - c)/eps;
    m.nand_b = temp;

    temp = m.and_w1;
    m.and_w1 += eps;
    temp_modle.and_w1 = (cost(m) - c)/eps;
    m.and_w1 = temp;

    temp = m.and_w2;
    m.and_w2 += eps;
    temp_modle.and_w2 = (cost(m) - c)/eps;
    m.and_w2 = temp;

    temp = m.and_b;
    m.and_b += eps;
    temp_modle.and_b = (cost(m) - c)/eps;
    m.and_b = temp;

    return temp_modle;
}

Xor diffence(Xor m, Xor g, float rate) {
    m.or_w1 -= g.or_w1 * rate;
    m.or_w2 -= g.or_w2 * rate;
    m.or_b -= g.or_b * rate;
    m.nand_w1 -= g.nand_w1 * rate;
    m.nand_w2 -= g.nand_w2 * rate;
    m.nand_b -= g.nand_b * rate;
    m.and_w1 -= g.and_w1 * rate;
    m.and_w2 -= g.and_w2 * rate;
    m.and_b -= g.and_b * rate;
    return m;
}

Xor struct_init() {
    Xor m;
    m.or_w1 = (float)rand()/RAND_MAX;
    m.or_w2 = (float)rand()/RAND_MAX;
    m.or_b = (float)rand()/RAND_MAX;
    m.nand_w1 = (float)rand()/RAND_MAX;
    m.nand_w2 = (float)rand()/RAND_MAX;
    m.nand_b = (float)rand()/RAND_MAX;
    m.and_w1 = (float)rand()/RAND_MAX;
    m.and_w2 = (float)rand()/RAND_MAX;
    m.and_b = (float)rand()/RAND_MAX;
    return m;
}

void print_modle(Xor m) {
    printf("or w1 => %f, or w2 => %f, or b => %f\n", m.or_w1, m.or_w2, m.or_b);
    printf("nand w1 => %f, nand w2 => %f, nand b => %f\n", m.nand_w1, m.nand_w2, m.nand_b);
    printf("and w1 => %f, and w2 => %f, and b => %f\n", m.and_w1, m.and_w2, m.and_b);
}

int main(void) {
    srand(time(0));
    Xor modle = struct_init();

    float eps = 1e-3;
    float rate = 1e-2;

    for (int i = 0; i < 1000*1000; i++) {
        // print_modle(modle);
        float c = cost(modle);
        printf("cost => %f\n", c);
        modle = diffence(modle, finite_difference(modle, eps), rate);
    }
    // printf("cost => %f\n", cost(modle));

    printf("or\n");
    for(int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d %d => %f\n", i, j, sigmoid_func(i * modle.or_w1 + j * modle.or_w2 + modle.or_b));
        }
    }
    printf("nand\n");
    for(int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d %d => %f\n", i, j, sigmoid_func(i * modle.nand_w1 + j * modle.nand_w2 + modle.nand_b));
        }
    }
    printf("and\n");
    for(int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d %d => %f\n", i, j, sigmoid_func(i * modle.and_w1 + j * modle.and_w2 + modle.and_b));
        }
    }
    printf("XOR\n");
    for(int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d %d => %f\n", i, j, forward(modle, i, j));
        }
    }


    return 0;
}
