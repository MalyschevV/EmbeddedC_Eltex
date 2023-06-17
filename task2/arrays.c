#include <stdio.h>
#include <malloc.h>

void PrintOrderedMatrix(int **matrix, int *size){
   for(int i = 0; i < *size; i++){
     for(int j = 0; j < *size; j++){
       matrix[i][j] = (j+1)+((*size)*i);
       printf("%3d ", matrix[i][j]);
     }
     printf("\n");
   }
}

void ReversedArray(int *array, int *size){
    for(int i = 0; i < *size; i++){
    array[i] = i+1;
    printf("%3d ",array[i]);
  }
  printf("\n");
  
  for(int i = 0; i < *size/2; i++){
    int tmp = array[i];
    array[i] = array[(*size-1-i)];
    array[(*size-1-i)] = tmp;
  }

  for(int i = 0; i < *size; i++){
    printf("%3d ",array[i]);
  }
}

void MatrixDiagonals(int **matrix, int *size){
    for(int i = 0; i < *size; i++){
    for(int j = 0; j < *size; j++){
      if(i == j){
        matrix[i][j] = *size;
      }
      else if(i < j){
        matrix[i][j] = 1;
      }
      else{
        matrix[i][j] = 0;
      }
      printf("%3d ", matrix[i][j]);
    }
    printf("\n");
  }
}

void SpiralMatrix(int **matrix, int *size){
  matrix[(*size)/2][(*size)/2] = (*size) * (*size);
  int counter = 1;
  for (int i = 1; i <= *size / 2; i++) {
    for (int j = i - 1; j < *size - i + 1; j++) {
      matrix[i - 1][j] = counter++;
    }
    for (int j = i; j < *size - i + 1; j++) {
      matrix[j][*size - i] = counter++;
    }
    for (int j = *size - i - 1; j >= i - 1; --j) {
      matrix[*size - i][j] = counter++;
    }
    for (int j = *size - i - 1; j >= i; j--) {
      matrix[j][i - 1] = counter++;
    }
  }
  for (int i = 0; i < *size; i++) {
    for (int j = 0; j < *size; j++) {
      printf("%3d ", matrix[i][j]);
    }
    printf("\n");
  }
}
  
int main() {
  int size  = 0;
  int **matrix = NULL;
  int *array = NULL;
  printf("enter a size for arrays and matrixes\n");
  scanf("%d", &size);
  
  matrix = (int**) malloc(size * sizeof(int*));
  matrix[0] = (int*) malloc(size * size * sizeof(int));
  for (int i = 1; i < size; i++) {
    matrix[i] = matrix[0] + i * size;
}
  if(NULL != matrix){
    printf("\nOrdered matrix:\n\n");
    PrintOrderedMatrix(matrix,  &size);
    printf("\nDiagonals of a matrix:\n\n");
    MatrixDiagonals(matrix, &size);
    printf("\nSpiral matrix:\n\n");
    SpiralMatrix(matrix, &size);
  }
  free(matrix[0]);
  free(matrix);
  matrix = NULL;
  
  array = (int*)malloc(size * sizeof(int));
  if(NULL != array){
    printf("\nReversed array:\n\n");
    ReversedArray(array, &size);
  }
  free(array);
  printf("\n");
  return 0;
}
