#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-07

enum {
  OK = 0,
  INCORRECT_MATRIX = 1,
  CALC_ERROR = 2,
};
enum { FAILURE = 0, SUCCESS = 1 };

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
// int s21_eq_matrix(matrix_t *A, matrix_t *B);
// int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// int s21_transpose(matrix_t *A, matrix_t *result);
// int s21_calc_complements(matrix_t *A, matrix_t *result);
// int s21_determinant(matrix_t *A, double *result);
// int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// helpers ?

// void get_submatrix(matrix_t *A, int rowToRemove, int colToRemove,
//                    matrix_t *submatrix);
// int check_matrix(matrix_t *A);
// double get_determinant(matrix_t *A);
// int s21_is_correct_(matrix_t *A);

#endif  // SRC_S21_MATRIX_H_
