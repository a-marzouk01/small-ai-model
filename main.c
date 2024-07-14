#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int sample[3];

sample and_train[] = {
    {0, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {1, 1, 1},
};

sample or_train[] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1},
};

sample nand_train[] = {
    {0, 0, 1},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0},
};

sample *train = nand_train;
int train_size = 4;

float sigmoid_func(float sum) {
    return 1 / (1 + exp(-sum));
}

float cost(float weight1, float weight2, float bias) {
    float sum = 0;
    for (int i = 0; i < train_size; i++) {
        float input1 = train[i][0];
        float input2 = train[i][1];
        float output = train[i][2];
        float prediction = sigmoid_func(input1 * weight1 + input2 * weight2 + bias);
        float error = prediction - output;
        sum += error * error;
    }
    sum /= (float) train_size;

    return sum;
}

int main(int argc, char *argv[]) {
    srand(time(0));
    float weight1 = (float)rand()/RAND_MAX;
    float weight2 = (float)rand()/RAND_MAX;
    float bias = (float)rand()/RAND_MAX;

    float eps = 1e-3 ;
    float rate = 1e-2;

    float sum = 0;
    for(int j = 0; j < 1000*1000; j++){
        float costf = cost(weight1, weight2, bias);
        float dweight1 = (cost(weight1 + eps, weight2, bias) - costf) / eps;
        float dweight2 = (cost(weight1, weight2 + eps, bias) - costf) / eps;
        float dbias    = (cost(weight1, weight2, bias + eps) - costf) / eps;
        weight1 -= rate * dweight1;
        weight2 -= rate * dweight2;
        bias    -= rate * dbias;
        // printf("cost => %f, bais => %f\n", costf, bias);
    }
    printf("cost => %f, bais => %f\n", cost(weight1, weight2, bias), bias);
    printf("weight1 => %f, weight2 => %f\n", weight1, weight2);

    for(int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d %d => %f\n", i, j, sigmoid_func(i * weight1 + j * weight2 + bias));
        }
    }

   return 0;
}
