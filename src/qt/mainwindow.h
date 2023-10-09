#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>

#include "QtGifImage/src/gifimage/qgifimage.h"
extern "C" {
#include "../model.h"
#include "../settings.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QTimer *timer;
  float count = 0;
  QVector<QImage> gif;

  void makeGIF();

 private slots:

  void timerRun();

  void on_xTurnButton_clicked();

  void on_shiftButton_clicked();

  void on_yTurnButton_clicked();

  void on_scaleButton_clicked();

  void on_zTurnButton_clicked();

  void on_resizeButton_clicked();

  void on_snapshotButton_clicked();

  void on_pushButton_OpenFile_clicked();

  void on_comboBox_projectionType_currentIndexChanged(int index);

  void on_pointSizeInput_valueChanged(int arg1);

  void on_vertexType_currentIndexChanged(int index);

  void on_edgeSize_valueChanged(int arg1);

  void on_comboBox_edgesType_currentIndexChanged(int index);

  void on_pushButton_backColor_clicked();

  void on_pushButton_vertexColor_clicked();

  void on_pushButton_edgeColor_clicked();

  void on_radioButton_clicked();

  void on_radioButton_2_clicked();

  void on_pushButton_saveOptions_clicked();

  void on_doubleSpinBox_focus_dist_valueChanged(double arg1);

  void on_scaleInputSlider_valueChanged(int value);

  void on_restoreOptionsButton_clicked();

  void on_gifMakeButton_clicked();

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
