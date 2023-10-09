#include "model.h"

// Функция чтения количества вершин и граней из файла
int read_count_of_vertex_and_faces(const char *filename, unsigned *cv,
                                   unsigned *cf) {
  int status = 0;
  FILE *file = fopen(filename, "r");

  if (!file) {
    status = 1;  // Не смогли открыть файл
  } else {
    char line[500];
    *cv = 0;
    *cf = 0;
    while (fgets(line, sizeof(line), file)) {
      if (!strncmp(line, "v ", 2))
        (*cv)++;
      else if (!strncmp(line, "f ", 2))
        (*cf)++;
    }
    fclose(file);
  }
  if (status != 1 && (!*cv || !*cf)) status = 2;

  return status;  // если нет вершин и нет полигонов то возвращаем ошибку
}

// Функция выделения памяти для модели
void calloc_model(model *m, unsigned cv, unsigned cf) {
  // Выделение памяти для матрицы точек
  s21_create_matrix(3, cv, &m->point);
  // Выделение памяти для граней
  m->poligon.count = cf;
  m->poligon.poligon_data = (poligon_data *)calloc(cf, sizeof(poligon_data));
}

// Функция чтения модели из файла
int read_model(model *m, const char *filename) {
  int status = 0;
  unsigned count_v = 0, count_f = 0;
  FILE *file = fopen(filename, "r");
  char line[500];
  if (!file) {
    return 1;  // Не удалось открыть файл
  }

  while (fgets(line, sizeof(line), file)) {
    if (!strncmp(line, "v ", 2)) {
      double px = NAN, py = NAN, pz = NAN;
      if (sscanf(line + 2, "%lf %lf %lf", &px, &py, &pz) != 3) {
        status = 2;  // Неверный формат строки
        break;
      }
      add_point(m, count_v, px, py, pz);
      count_v++;
    } else if (!strncmp(line, "f ", 2)) {
      int len = 0;
      int x;
      if (sscanf(line + 2, "%d", &x) != 1) {
        status = 2;  // Неверный формат строки
        break;
      }

      len++;
      m->poligon.poligon_data[count_f].array = (int *)malloc(sizeof(int));
      m->poligon.poligon_data[count_f].array[0] =
          (m->point.columns + x) % (m->point.columns + 1);

      char *str = line + 2;
      while (sscanf(str, "%d", &x) == 1) {
        len++;
        m->poligon.poligon_data[count_f].array = (int *)realloc(
            m->poligon.poligon_data[count_f].array, len * sizeof(int));
        if (m->poligon.poligon_data[count_f].array == NULL) {
          status = 3;  // Ошибка выделения памяти
          break;
        }
        m->poligon.poligon_data[count_f].array[len - 1] =
            (m->point.columns + x) % (m->point.columns + 1);

        while (*str != ' ' && *str != '\0') {
          str++;
        }
        while (*str == ' ') {
          str++;
        }
      }
      m->poligon.poligon_data[count_f].lenght = len;
      count_f++;
    }
  }

  fclose(file);
  return status;
}

// Функция добавления точки в модель
void add_point(model *m, unsigned count_v, double px, double py, double pz) {
  if ((int)count_v < m->point.columns) {
    m->point.matrix[0][count_v] = px;
    m->point.matrix[1][count_v] = py;
    m->point.matrix[2][count_v] = pz;
  }
}

// Функция освобождения памяти, занимаемой моделью
void free_model(model *m) {
  s21_remove_matrix(&m->point);
  for (unsigned i = 0; i < m->poligon.count; i++) {
    free(m->poligon.poligon_data[i].array);
  }
  free(m->poligon.poligon_data);
  m->poligon.count = 0;
}
