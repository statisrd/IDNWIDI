#include "model.h"

// Функция для подсчета общего количества ребер в модели
unsigned long get_count_of_edges(model *m) {
  unsigned long result = 0;
  for (unsigned i = 0; i < m->poligon.count; i++) {
    result += m->poligon.poligon_data[i].lenght;

    // Каждая грань добавляет одно дополнительное ребро
    result += 1;
  }
  return result;
}
