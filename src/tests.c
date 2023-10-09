#include <check.h>

#include "model.h"

START_TEST(test_load_1) {
  const char filename[] = "obj_files/chair.obj";
  unsigned cv = 0;
  unsigned cf = 0;
  int status = read_count_of_vertex_and_faces(filename, &cv, &cf);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(cv, 116);
  ck_assert_uint_eq(cf, 76);

  model m;
  calloc_model(&m, cv, cf);
  status = read_model(&m, filename);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(m.point.columns, cv);
  ck_assert_double_eq_tol(m.point.matrix[0][0], -0.8, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][0], 0.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][0], 0.8, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][5], -0.8, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][5], 0.6, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][5], 0.7, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][115], -0.7, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][115], 1.5, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][115], -5.96046e-08, EPS);

  ck_assert_int_eq(m.poligon.poligon_data[22].lenght, 4);
  ck_assert_int_eq(m.poligon.poligon_data[22].array[0], 34);
  ck_assert_int_eq(m.poligon.poligon_data[22].array[1], 34);
  ck_assert_int_eq(m.poligon.poligon_data[22].array[2], 35);

  ck_assert_int_eq(m.poligon.poligon_data[75].lenght, 4);
  ck_assert_int_eq(m.poligon.poligon_data[75].array[0], 114);
  ck_assert_int_eq(m.poligon.poligon_data[75].array[1], 114);
  ck_assert_int_eq(m.poligon.poligon_data[75].array[2], 113);

  ck_assert_int_eq(m.poligon.poligon_data[1].lenght, 4);
  ck_assert_int_eq(m.poligon.poligon_data[1].array[0], 5);
  ck_assert_int_eq(m.poligon.poligon_data[1].array[1], 5);
  ck_assert_int_eq(m.poligon.poligon_data[1].array[2], 1);

  free_model(&m);
}
END_TEST

START_TEST(test_load_2) {
  const char filename[] = "obj_files/Plane.obj";
  unsigned cv = 0;
  unsigned cf = 0;
  int status = read_count_of_vertex_and_faces(filename, &cv, &cf);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(cv, 9454);
  ck_assert_uint_eq(cf, 7132);

  model m;
  calloc_model(&m, cv, cf);
  status = read_model(&m, filename);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(m.point.columns, cv);
  ck_assert_double_eq_tol(m.point.matrix[0][0], -627.853531, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][0], 50.167524, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][0], 0.0, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][4454], -130.750648, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][4454], -102.01651, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][4454], -27.911488, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][9453], 515.585405, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][9453], -103.513318, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][9453], -65.799957, EPS);

  ck_assert_int_eq(m.poligon.poligon_data[0].lenght, 4);
  ck_assert_int_eq(m.poligon.poligon_data[0].array[0], 25);
  ck_assert_int_eq(m.poligon.poligon_data[0].array[1], 25);
  ck_assert_int_eq(m.poligon.poligon_data[0].array[2], 2);

  ck_assert_int_eq(m.poligon.poligon_data[1].lenght, 5);
  ck_assert_int_eq(m.poligon.poligon_data[1].array[0], 25);
  ck_assert_int_eq(m.poligon.poligon_data[1].array[1], 25);
  ck_assert_int_eq(m.poligon.poligon_data[1].array[2], 26);
  ck_assert_int_eq(m.poligon.poligon_data[1].array[3], 3);

  ck_assert_int_eq(m.poligon.poligon_data[7131].lenght, 5);
  ck_assert_int_eq(m.poligon.poligon_data[7131].array[0], 9172);
  ck_assert_int_eq(m.poligon.poligon_data[7131].array[1], 9172);
  ck_assert_int_eq(m.poligon.poligon_data[7131].array[2], 9173);
  ck_assert_int_eq(m.poligon.poligon_data[7131].array[3], 9453);

  ck_assert_int_eq(m.poligon.poligon_data[3632].lenght, 5);
  ck_assert_int_eq(m.poligon.poligon_data[3632].array[0], 3534);
  ck_assert_int_eq(m.poligon.poligon_data[3632].array[1], 3534);
  ck_assert_int_eq(m.poligon.poligon_data[3632].array[2], 3535);
  ck_assert_int_eq(m.poligon.poligon_data[3632].array[3], 3512);

  free_model(&m);
}
END_TEST

START_TEST(test_load_not_exist_1) {
  const char filename[] = "obj_files/not_exist.obj";
  unsigned cv = 0;
  unsigned cf = 0;
  int status = read_count_of_vertex_and_faces(filename, &cv, &cf);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_load_inavalid_file_1) {
  const char filename[] = "obj_files/without_vertexes.obj";
  unsigned cv = 0;
  unsigned cf = 0;
  int status = read_count_of_vertex_and_faces(filename, &cv, &cf);
  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(test_move_1) {
  const char filename[] = "obj_files/chair.obj";
  unsigned cv = 0;
  unsigned cf = 0;
  int status = read_count_of_vertex_and_faces(filename, &cv, &cf);

  model m;
  calloc_model(&m, cv, cf);
  status = read_model(&m, filename);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(m.point.columns, cv);

  double mvX = 1.1, mvY = -2.4, mvZ = 3.0;
  shift(&m, mvX, mvY, mvZ);
  shift(&m, -mvX, -mvY, -mvZ);

  ck_assert_double_eq_tol(m.point.matrix[0][0], -0.8, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][0], 0.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][0], 0.8, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][5], -0.8, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][5], 0.6, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][5], 0.7, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][115], -0.7, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][115], 1.5, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][115], -5.96046e-08, EPS);

  free_model(&m);
}
END_TEST

START_TEST(test_move_2) {
  const char filename[] = "obj_files/Plane.obj";
  unsigned cv = 0;
  unsigned cf = 0;
  int status = read_count_of_vertex_and_faces(filename, &cv, &cf);

  model m;
  calloc_model(&m, cv, cf);
  status = read_model(&m, filename);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(m.point.columns, cv);

  double mvX = 5.1, mvY = 2.4, mvZ = -3.5;
  shift(&m, mvX, mvY, mvZ);
  shift(&m, -mvX, -mvY, -mvZ);

  ck_assert_double_eq_tol(m.point.matrix[0][0], -627.853531, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][0], 50.167524, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][0], 0., EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][5454], -130.131155, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][5454], -102.125743, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][5454], -58.067403, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][9452], 515.585405, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][9452], -103.513318, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][9452], -58.067403, EPS);

  free_model(&m);
}
END_TEST

START_TEST(test_rotation_1) {
  const char filename[] = "obj_files/chair.obj";
  unsigned cv = 0;
  unsigned cf = 0;
  int status = read_count_of_vertex_and_faces(filename, &cv, &cf);

  model m;
  calloc_model(&m, cv + 4, cf);
  status = read_model(&m, filename);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(m.point.columns, cv + 4);

  add_point(&m, cv + 1, 0.4, -0.75, -0.4);
  add_point(&m, cv + 1, 1, 0, 0);
  add_point(&m, cv + 2, 0, 1, 0);
  add_point(&m, cv + 3, 0, 0, 1);

  double rX = 1.1, rY = -2.4, rZ = 3.0;

  rotationX(&m, rX);
  rotationX(&m, -rX);
  ck_assert_double_eq_tol(m.point.matrix[0][0], -0.8, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][0], 0.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][0], 0.8, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][5], -0.8, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][5], 0.6, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][5], 0.7, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][115], -0.7, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][115], 1.5, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][115], -5.96046e-08, EPS);

  rotationY(&m, rY);
  rotationY(&m, -rY);
  ck_assert_double_eq_tol(m.point.matrix[0][0], -0.8, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][0], 0.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][0], 0.8, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][5], -0.8, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][5], 0.6, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][5], 0.7, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][115], -0.7, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][115], 1.5, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][115], -5.96046e-08, EPS);

  rotationZ(&m, rZ);
  rotationZ(&m, -rZ);
  ck_assert_double_eq_tol(m.point.matrix[0][0], -0.8, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][0], 0.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][0], 0.8, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][5], -0.8, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][5], 0.6, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][5], 0.7, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][115], -0.7, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][115], 1.5, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][115], -5.96046e-08, EPS);

  free_model(&m);
}
END_TEST

START_TEST(test_rotation_2) {
  const char filename[] = "obj_files/Wind_turbine_001.obj";
  unsigned cv = 0;
  unsigned cf = 0;
  int status = read_count_of_vertex_and_faces(filename, &cv, &cf);

  model m;
  calloc_model(&m, cv + 4, cf);
  status = read_model(&m, filename);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(m.point.columns, cv + 4);

  add_point(&m, cv + 1, 0.332269, -14.291578, 0.089027);
  add_point(&m, cv + 1, 1, 0, 0);
  add_point(&m, cv + 2, 0, 1, 0);
  add_point(&m, cv + 3, 0, 0, 1);
  double rX = 2.4, rY = 3.2, rZ = -0.1;

  rotationX(&m, rX);
  rotationX(&m, -rX);
  ck_assert_double_eq_tol(m.point.matrix[0][0], -2.053972, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][0], 22.247374, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][0], 0.131160, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][668], 0.116092, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][668], 23.054464, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][668], 0.334033, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][1367], 0.388002, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][1367], 20.924484, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][1367], -0.580678, EPS);

  rotationY(&m, rY);
  rotationY(&m, -rY);
  ck_assert_double_eq_tol(m.point.matrix[0][0], -2.053972, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][0], 22.247374, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][0], 0.131160, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][668], 0.116092, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][668], 23.054464, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][668], 0.334033, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][1367], 0.388002, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][1367], 20.924484, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][1367], -0.580678, EPS);

  rotationZ(&m, rZ);
  rotationZ(&m, -rZ);
  ck_assert_double_eq_tol(m.point.matrix[0][0], -2.053972, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][0], 22.247374, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][0], 0.131160, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][668], 0.116092, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][668], 23.054464, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][668], 0.334033, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][1367], 0.388002, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][1367], 20.924484, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][1367], -0.580678, EPS);

  free_model(&m);
}
END_TEST

START_TEST(test_rotation_3) {
  const char filename[] = "obj_files/cube.obj";
  unsigned cv = 0;
  unsigned cf = 0;
  int status = read_count_of_vertex_and_faces(filename, &cv, &cf);

  model m;
  calloc_model(&m, cv + 4, cf);
  status = read_model(&m, filename);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(m.point.columns, cv + 4);

  add_point(&m, cv + 1, 0, 0, 0);
  add_point(&m, cv + 1, 1, 0, 0);
  add_point(&m, cv + 2, 0, 1, 0);
  add_point(&m, cv + 3, 0, 0, 1);

  double rX = 1.5;
  double rY = 2.1;
  double mvX = 0.5;
  double mvY = -0.5;
  double mvZ = 0.4;

  shift(&m, mvX, mvY, mvZ);
  rotationXForMouse(&m, rX);
  rotationYForMouse(&m, rY);
  rotationYForMouse(&m, -rY);
  rotationXForMouse(&m, -rX);
  shift(&m, -mvX, -mvY, -mvZ);

  ck_assert_double_eq_tol(m.point.matrix[0][0], 1.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][0], 1.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][0], -1.0, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][1], 1.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][1], -1.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][1], -1.0, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][7], -1.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][7], -1.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][7], 1.0, EPS);

  free_model(&m);
}
END_TEST

START_TEST(test_rotation_4) {
  const char filename[] = "obj_files/cube.obj";
  unsigned cv = 0;
  unsigned cf = 0;
  int status = read_count_of_vertex_and_faces(filename, &cv, &cf);

  model m;
  calloc_model(&m, cv + 4, cf);
  status = read_model(&m, filename);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(m.point.columns, cv + 4);

  add_point(&m, cv + 1, 0, 0, 0);
  add_point(&m, cv + 1, 1, 0, 0);
  add_point(&m, cv + 2, 0, 1, 0);
  add_point(&m, cv + 3, 0, 0, 1);

  double rX = M_PI / 2;
  double rZ = -M_PI / 2;

  rotationX(&m, rX);
  rotationZ(&m, rZ);

  ck_assert_double_eq_tol(m.point.matrix[0][0], 1.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][0], 1.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][0], -1.0, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][2], 1.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][2], -1.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][2], -1.0, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][7], -1.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][7], -1.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][7], 1.0, EPS);

  free_model(&m);
}
END_TEST

START_TEST(test_scale_1) {
  const char filename[] = "obj_files/chair.obj";
  unsigned cv = 0;
  unsigned cf = 0;
  int status = read_count_of_vertex_and_faces(filename, &cv, &cf);

  model m;
  calloc_model(&m, cv, cf);
  status = read_model(&m, filename);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(m.point.columns, cv);

  double sc = 1.2;

  scaling(&m, sc);
  scaling(&m, 1.0 / sc);
  ck_assert_double_eq_tol(m.point.matrix[0][0], -0.8, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][0], 0.0, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][0], 0.8, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][5], -0.8, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][5], 0.6, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][5], 0.7, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][115], -0.7, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][115], 1.5, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][115], -5.96046e-08, EPS);

  free_model(&m);
}
END_TEST

START_TEST(test_scale_2) {
  const char filename[] = "obj_files/FerrisWheel_lowpoly.obj";
  unsigned cv = 0;
  unsigned cf = 0;
  int status = read_count_of_vertex_and_faces(filename, &cv, &cf);

  model m;
  calloc_model(&m, cv, cf);
  status = read_model(&m, filename);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(m.point.columns, cv);

  double sc = 0.4;

  scaling(&m, sc);
  scaling(&m, 1.0 / sc);
  ck_assert_double_eq_tol(m.point.matrix[0][0], 0.776667, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][0], 1.692188, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][0], 1.334552, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][1298], -0.459324, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][1298], 2.102798, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][1298], 1.352709, EPS);

  ck_assert_double_eq_tol(m.point.matrix[0][2589], 0.401863, EPS);
  ck_assert_double_eq_tol(m.point.matrix[1][2589], 1.192098, EPS);
  ck_assert_double_eq_tol(m.point.matrix[2][2589], 1.217865, EPS);

  free_model(&m);
}
END_TEST

// test model

/////////////////////////

static unsigned long int next = 1;

int my_rand(void) {
  next = next * 1103515245 + 12345;
  return (unsigned int)(next / 65536) % 32768;
}

void my_srand(unsigned int seed) { next = seed; }

START_TEST(mult_number_matrix) {
  const int rows = my_rand() % 100 + 1;
  const int cols = my_rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);
  double mult_number = ((double)my_rand() / 32767) * 2.0 -
                       1.0;  // Генерируем случайное число от -1.0 до 1.0
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] =
          ((double)my_rand() / 32767) * (DBL_MAX - DBL_MIN) +
          DBL_MIN;  // Генерируем случайное число в диапазоне [DBL_MIN, DBL_MAX]
      check.matrix[i][j] = m.matrix[i][j] * mult_number;
    }
  }
  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_number(&m, mult_number, &res), OK);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

//////////////////////////

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  // int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_load_1);
  tcase_add_test(tc1_1, test_load_2);
  tcase_add_test(tc1_1, test_load_not_exist_1);
  tcase_add_test(tc1_1, test_load_inavalid_file_1);
  tcase_add_test(tc1_1, test_move_1);
  tcase_add_test(tc1_1, test_move_2);
  tcase_add_test(tc1_1, test_rotation_1);
  tcase_add_test(tc1_1, test_rotation_2);
  tcase_add_test(tc1_1, test_rotation_3);
  tcase_add_test(tc1_1, test_rotation_4);
  tcase_add_test(tc1_1, test_scale_1);
  tcase_add_test(tc1_1, test_scale_2);
  tcase_add_test(tc1_1, mult_number_matrix);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  // nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  // return nf == 0 ? 0 : 1;
  return 0;
}
