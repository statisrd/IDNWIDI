#ifndef _MODEL_H_
#define _MODEL_H_
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "matrix/s21_matrix.h"

typedef struct data_poligon {
  int *array;
  unsigned lenght;
} poligon_data;

typedef struct array_poligons {
  poligon_data *poligon_data;
  unsigned count;
} Poligon;

typedef struct data {
  matrix_t point;
  Poligon poligon;
} model;

// прочитать файл и записать в переменные количество вершин и поверхностей
int read_count_of_vertex_and_faces(const char *filename, unsigned *cv,
                                   unsigned *cf);

// выделить память для структуры
void calloc_model(model *m, unsigned cv, unsigned cf);
// Заполнить структуру модели(для которой уже выделена память) из файла
int read_model(model *m, const char *filename);

// Добавить точку с координатами (x,y,z) в матрицу точек под номером
// pos(номер столбца)
void add_point(model *m, unsigned pos, double px, double py, double pz);

// освободить память модели
void free_model(model *m);

//  вычисляет новые координаты при сдвиге объекта
void shift(model *object, double xShift, double yShift, double zShift);

//  вычисляет новые координаты при масштабировании объекта
void scaling(model *object, double scale);

//  вычисляет новые координаты после поворота фигуры вокруг собственной оси X
void rotationX(model *object, double xTurn);

//  вычисляет новые координаты после поворота фигуры вокруг собственной оси Y
void rotationY(model *object, double xTurn);

//  вычисляет новые координаты после поворота фигуры вокруг собственной оси Z
void rotationZ(model *object, double xTurn);

//  находит максимальное и минимальное значения координат
void MinMax(model *object, double *edges);

//  перемещает модель в центр видимой области, меняет размер модели
void calibration(model *object);

//  пересчитывает ребра модели
unsigned long get_count_of_edges(model *m);

//  вычисляет новые координаты после поворота фигуры вокруг оси, параллельной
//  оси X виджета
void rotationXForMouse(model *object, double xTurn);

//  вычисляет новые координаты после поворота фигуры вокруг оси, параллельной
//  оси Y виджета
void rotationYForMouse(model *object, double xTurn);

#endif  // _MODEL_H_
