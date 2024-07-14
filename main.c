#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int data[][2] = {
    {0, 0},
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},
    {5, 10}
};

#define train_size sizeof(data)/sizeof(data[0][0])

float cost(float w) {
    float sum = 0;
    for (int i = 0; i < train_size; i++) {
        float x = data[i][0];
        float y = data[i][1];
        float prediction = x * w;
        float error = y - prediction;
        sum += error * error;
    }
    sum /= (float) train_size;

    return sum;
}

int main(int argc, char *argv[]) {
    srand(69);
    float weight = (float)rand()/RAND_MAX;

    float eps = 1e-3;
    float rate = 1e-3;

    float sum = 0;
    for(int j = 0; j < 1000; j++){
        float dweight = (cost(weight + eps) - cost(weight)) / eps;
        weight -= rate * dweight;
        printf("cost => %f\n", cost(weight));
    }
    printf("weight => %f\n", weight);
}
