#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QMouseEvent>
#include <QOpenGLWidget>

extern "C" {
#include "../model.h"
#include "../settings.h"
}

class modelView : public QOpenGLWidget {
 public:
  modelView(QWidget *parent = 0);
  ~modelView();

  model object;
  matrix_t *backupPoint;
  double xTurn, yTurn;
  QPoint mPos;
  int isLoaded;
  widgetOptions options;
  double focus_dist;

  // QOpenGLWidget interface
  //    protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  int loadModel(QString s);
  void updateProjection();

  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  void wheelEvent(QWheelEvent *);
};

#endif  // MODELVIEW_H
