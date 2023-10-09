#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int i, j, k;
  if (A->columns != B->rows) return INCORRECT_MATRIX;
  result->rows = A->rows;
  result->columns = B->columns;
  result->matrix = (double **)malloc(result->rows * sizeof(double *));
  if (result->matrix == NULL) return INCORRECT_MATRIX;
  for (i = 0; i < result->rows; i++) {
    result->matrix[i] = (double *)malloc(result->columns * sizeof(double));
    if (result->matrix[i] == NULL) return INCORRECT_MATRIX;
    for (j = 0; j < result->columns; j++) {
      result->matrix[i][j] = 0;
      for (k = 0; k < A->columns; k++)
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
    }
  }
  return OK;
}