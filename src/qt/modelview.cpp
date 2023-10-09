#include "modelview.h"

modelView::modelView(QWidget *parent) : QOpenGLWidget(parent) {
  isLoaded = 0;
  focus_dist = 1.0;
  if (loadOptions("settings.txt", &options)) {
    options.pointType = 0;
    options.pointSize = 5;
    options.pointColor[0] = 1;
    options.pointColor[1] = 1;
    options.pointColor[2] = 1;
    options.projectionType = 0;
    options.edgeColor[0] = 0.1;
    options.edgeColor[1] = 0.1;
    options.edgeColor[2] = 1;
    options.backColor[0] = 0.5;
    options.backColor[1] = 0.5;
    options.backColor[2] = 0.5;
    options.edgeSize = 1;
    options.edgeType = 0;
  }
}

modelView::~modelView() {
  if (isLoaded) {
    free_model(&object);
    s21_remove_matrix(backupPoint);
  }
}

int modelView::loadModel(QString s) {
  char filename[1000];
  qstrncpy(filename, s.toStdString().c_str(), s.length() + 1);
  unsigned cv = 0;
  unsigned cf = 0;
  int status = read_count_of_vertex_and_faces(filename, &cv, &cf);
  if (!status) {
    calloc_model(&object, cv + 4, cf);
    status = read_model(&object, filename);
    if (!status) {
      add_point(&object, cv, object.point.matrix[0][cv - 1],
                object.point.matrix[1][cv - 1], object.point.matrix[2][cv - 1]);
      add_point(&object, cv + 1, object.point.matrix[0][cv - 1],
                object.point.matrix[1][cv - 1], object.point.matrix[2][cv - 1]);
      add_point(&object, cv + 2, object.point.matrix[0][cv - 1],
                object.point.matrix[1][cv - 1], object.point.matrix[2][cv - 1]);
      add_point(&object, cv + 3, object.point.matrix[0][cv - 1],
                object.point.matrix[1][cv - 1], object.point.matrix[2][cv - 1]);
      calibration(&object);
      backupPoint = (matrix_t *)malloc(sizeof(matrix_t));
      s21_create_matrix(3, object.point.columns, backupPoint);
      s21_mult_number(&(object.point), 1, backupPoint);
    }
  }
  return status;
}

void modelView::initializeGL() {
  glClearColor(options.backColor[0], options.backColor[1], options.backColor[2],
               1.0f);
}

void modelView::updateProjection() {
  if (options.projectionType == 0) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float near = focus_dist;
    float far = near + 2;
    glFrustum(-1, 1, -1, 1, near, far);
    glTranslated(0, 0, -(near + far) / 2);
  }
}

void modelView::paintGL() {
  glClearColor(options.backColor[0], options.backColor[1], options.backColor[2],
               1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  updateProjection();

  if (isLoaded) {
    if (options.pointType) {
      glColor3d(options.pointColor[0], options.pointColor[1],
                options.pointColor[2]);
      glPointSize(options.pointSize);
      if (options.pointType == 1) glDisable(GL_POINT_SMOOTH);
      if (options.pointType == 2) glEnable(GL_POINT_SMOOTH);
      glBegin(GL_POINTS);
      for (int i = 0; i < object.point.columns - 4; i++)
        glVertex3d(object.point.matrix[0][i], object.point.matrix[1][i],
                   object.point.matrix[2][i]);
      glEnd();
    }
    glLineWidth(options.edgeSize);
    if (options.edgeType) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(2, 58360);
    }
    if (!options.edgeType) glDisable(GL_LINE_STIPPLE);
    for (unsigned int j = 0; j < object.poligon.count; j++) {
      glBegin(GL_LINE_LOOP);
      glColor3d(options.edgeColor[0], options.edgeColor[1],
                options.edgeColor[2]);
      for (unsigned int i = 0; i < object.poligon.poligon_data[j].lenght; i++) {
        int vertex_index = object.poligon.poligon_data[j].array[i];
        glVertex3d(object.point.matrix[0][vertex_index],
                   object.point.matrix[1][vertex_index],
                   object.point.matrix[2][vertex_index]);
      }
      glEnd();
    }
  }
}

void modelView::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void modelView::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void modelView::wheelEvent(QWheelEvent *event) {
  QPoint numDegrees = event->angleDelta() / 8;
  scaling(&object, 1.0 + numDegrees.y() / 100.0);
  update();
}

void modelView::mouseMoveEvent(QMouseEvent *mo) {
  if (isLoaded) {
    xTurn = (mo->pos().y() - mPos.y());
    yTurn = (mo->pos().x() - mPos.x());
    if (mo->buttons() == Qt::LeftButton) {
      rotationXForMouse(&object, xTurn / 200.0);
      rotationYForMouse(&object, yTurn / 200.0);
    } else if (mo->buttons() == Qt::MiddleButton) {
      shift(&object, yTurn / 470.0, -xTurn / 470.0, 0.0);
    }
    mPos = mo->pos();
    update();
  }
}
