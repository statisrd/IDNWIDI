#ifndef _SETTINGS_H_
#define _SETTINGS_H_
#include <stdio.h>

typedef struct widgetOptions {
  int pointType;  //  0- вершины не отображаются,  1 - квадратные вершины, 2  -
                  //  вершины в виде кругов
  int pointSize;  //  размер вершин
  float pointColor[3];  //  цвет вершин

  int edgeType;  //  0 - сплошные линии, 1 - пунктирные линии
  int edgeSize;        //  толщина линий
  float edgeColor[3];  //  цвет линий

  float backColor[3];  //  цвет фона

  int projectionType;  //  тип проекции
} widgetOptions;

int saveOptions(const char *filename, widgetOptions wo);

int loadOptions(const char *filename, widgetOptions *wo);

#endif  // _SETTINGS_H_
