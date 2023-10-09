#include "settings.h"

// Функция загрузки настроек из файла
int loadOptions(const char* filename, widgetOptions* wo) {
  FILE* file = fopen(filename, "r");
  if (!file) return 1;  // Ошибка при открытии файла

  int status = 0;
  char line[64];
  int valuesRead = 0;

  while (fgets(line, sizeof(line), file)) {
    if (valuesRead == 0) {
      if (sscanf(line, "%d", &wo->pointType) != 1)
        status = 1;  // Ошибка при чтении значения pointType
    } else if (valuesRead == 1) {
      if (sscanf(line, "%d", &wo->pointSize) != 1)
        status = 1;  // Ошибка при чтении значения pointSize
    } else if (valuesRead == 2) {
      if (sscanf(line, "%d", &wo->edgeType) != 1)
        status = 1;  // Ошибка при чтении значения edgeType
    } else if (valuesRead == 3) {
      if (sscanf(line, "%d", &wo->edgeSize) != 1)
        status = 1;  // Ошибка при чтении значения edgeSize
    } else if (valuesRead == 4) {
      if (sscanf(line, "%d", &wo->projectionType) != 1)
        status = 1;  // Ошибка при чтении значения projectionType
    } else if (valuesRead >= 5 && valuesRead < 8) {
      float value = 0.0f;
      if (sscanf(line, "%f", &value) != 1)
        status = 1;  // Ошибка при чтении значений цветов
      wo->pointColor[valuesRead - 5] = value;
    } else if (valuesRead >= 8 && valuesRead < 11) {
      float value = 0.0f;
      if (sscanf(line, "%f", &value) != 1)
        status = 1;  // Ошибка при чтении значений цветов
      wo->edgeColor[valuesRead - 8] = value;
    } else if (valuesRead >= 11 && valuesRead < 14) {
      float value = 0.0f;
      if (sscanf(line, "%f", &value) != 1)
        status = 1;  // Ошибка при чтении значений цветов
      wo->backColor[valuesRead - 11] = value;
    } else {
      status = 1;  // Чтение слишком много строк
    }

    valuesRead++;

    if (valuesRead >= 14) {
      break;  // Мы прочитали все необходимые значения
    }
  }

  fclose(file);

  if (valuesRead < 14 || status != 0) {
    return 1;  // Не удалось прочитать все значения или произошла ошибка
  }

  return 0;
}

// Функция сохранения настроек в файл
int saveOptions(const char* filename, widgetOptions wo) {
  FILE* file = fopen(filename, "w");
  if (!file) return 1;  // Ошибка при открытии файла

  int status = 0;
  char line[64];

  sprintf(line, "%d\n%d\n%d\n%d\n%d\n", wo.pointType, wo.pointSize, wo.edgeType,
          wo.edgeSize, wo.projectionType);
  if (fputs(line, file) == EOF) status = 1;  // Ошибка при записи значения

  sprintf(line, "%f\n%f\n%f\n", wo.pointColor[0], wo.pointColor[1],
          wo.pointColor[2]);
  if (fputs(line, file) == EOF)
    status = 1;  // Ошибка при записи значений цветов

  sprintf(line, "%f\n%f\n%f\n", wo.edgeColor[0], wo.edgeColor[1],
          wo.edgeColor[2]);
  if (fputs(line, file) == EOF)
    status = 1;  // Ошибка при записи значений цветов

  sprintf(line, "%f\n%f\n%f\n", wo.backColor[0], wo.backColor[1],
          wo.backColor[2]);
  if (fputs(line, file) == EOF)
    status = 1;  // Ошибка при записи значений цветов

  fclose(file);

  if (status != 0) {
    return 1;  // Произошла ошибка при записи
  }

  return 0;
}
