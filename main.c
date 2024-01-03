#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int data[][2] = {
  {0, 0},
  {1, 3},
  {2, 6},
  {3, 9},
  {4, 12},
  {5, 15}
};

float sigmoid_func(float sum) {
  return 1 / (1 + exp(-sum));
}

int main(int argc, char *argv[]) {
  srand(69);

  float learning = 0.01;

  float weight = (float)rand()/RAND_MAX;
  float sum = 0;

  for(int j = 0; j < 26; j++){
    for (int i = 0; i < sizeof(data)/sizeof(data[0][0]); i++) {
      float x = data[i][0];
      float y = data[i][1];
      float prediction = x * weight;

      float error = y - prediction;

      sum += y;
      weight += learning * error * x;
    }
  }

  int input;
  scanf("%d", &input);
  float output = input * weight;
  printf("%f", output);

}
