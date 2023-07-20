#include "operations.h"

void PrintOrderedMatrix(int **matrix, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matrix[i][j] = (j + 1) + (size * i);
      printf("%3d ", matrix[i][j]);
    }
    printf("\n");
  }
}

int ReversedArray(int *array, int size) {
  for (int i = 0; i < size; i++) {
    array[i] = i + 1;
    printf("%3d ", array[i]);
  }
  printf("\n");

  for (int i = 0; i < size / 2; i++) {
    int tmp = array[i];
    array[i] = array[size - 1 - i];
    array[size - 1 - i] = tmp;
  }

  for (int i = 0; i < size; i++) {
    printf("%3d ", array[i]);
  }

  return 0;
}

int MatrixDiagonals(int **matrix, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i == j) {
        matrix[i][j] = size;
      } else if (i < j) {
        matrix[i][j] = 1;
      } else {
        matrix[i][j] = 0;
      }
      printf("%3d ", matrix[i][j]);
    }
    printf("\n");
  }

  return 0;
}

int SpiralMatrix(int **matrix, int size) {
  matrix[size / 2][size / 2] = size * size;
  int counter = 1;
  for (int i = 1; i <= size / 2; i++) {
    for (int j = i - 1; j < size - i + 1; j++) {
      matrix[i - 1][j] = counter++;
    }
    for (int j = i; j < size - i + 1; j++) {
      matrix[j][size - i] = counter++;
    }
    for (int j = size - i - 1; j >= i - 1; --j) {
      matrix[size - i][j] = counter++;
    }
    for (int j = size - i - 1; j >= i; j--) {
      matrix[j][i - 1] = counter++;
    }
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%3d ", matrix[i][j]);
    }
    printf("\n");
  }

  return 0;
}