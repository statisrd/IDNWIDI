#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int i, j;
  result->rows = A->rows;
  result->columns = A->columns;
  result->matrix = (double **)malloc(result->rows * sizeof(double *));
  if (result->matrix == NULL) return INCORRECT_MATRIX;
  for (i = 0; i < result->rows; i++) {
    result->matrix[i] = (double *)malloc(result->columns * sizeof(double));
    if (result->matrix[i] == NULL) return INCORRECT_MATRIX;
    for (j = 0; j < result->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] * number;
  }
  return OK;
}