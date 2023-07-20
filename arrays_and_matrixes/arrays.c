#include "operations.h"

int main() {
  int size = 0;
  int **matrix = NULL;
  int *array = NULL;

  printf("enter a size for arrays and matrixes\n");
  scanf("%d", &size);

  matrix = (int **)malloc(size * sizeof(int *));
  matrix[0] = (int *)malloc(size * size * sizeof(int));
  for (int i = 1; i < size; i++) {
    matrix[i] = matrix[0] + i * size;
  }
  if (NULL != matrix) {
    printf("\nOrdered matrix:\n\n");
    PrintOrderedMatrix(matrix, size);
    printf("\nDiagonals of a matrix:\n\n");
    MatrixDiagonals(matrix, size);
    printf("\nSpiral matrix:\n\n");
    SpiralMatrix(matrix, size);
  }

  free(matrix[0]);
  free(matrix);
  matrix = NULL;
  
  array = (int *)malloc(size * sizeof(int));
  if (NULL != array) {
    printf("\nReversed array:\n\n");
    ReversedArray(array, size);
  }

  free(array);
  array = NULL;

  return 0;
}
