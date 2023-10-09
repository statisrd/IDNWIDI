#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  setFixedSize(1364, 1064);
  ui->setupUi(this);
  ui->textEdit_modelInfo->setText("Not Loaded");
  ui->pointSizeInput->setValue(ui->model_view->options.pointSize);
  ui->vertexType->setCurrentIndex(ui->model_view->options.pointType);
  ui->edgeSize->setValue(ui->model_view->options.edgeSize);
  ui->comboBox_edgesType->setCurrentIndex(ui->model_view->options.edgeType);
  ui->comboBox_projectionType->setCurrentIndex(
      ui->model_view->options.projectionType);
  timer = new QTimer(0);
  connect(timer, SIGNAL(timeout()), this, SLOT(timerRun()));
}

MainWindow::~MainWindow() {
  delete timer;
  delete ui;
}

void MainWindow::on_xTurnButton_clicked() {
  if (ui->model_view->isLoaded) {
    double turn = ui->xTurnInput->value();
    if (ui->radioButton_2->isChecked()) turn *= 2 * M_PI / 360;
    if (turn) {
      rotationX(&(ui->model_view->object), turn);
      ui->model_view->update();
    }
  }
}

void MainWindow::on_yTurnButton_clicked() {
  if (ui->model_view->isLoaded) {
    double turn = ui->yTurnInput->value();
    if (ui->radioButton_2->isChecked()) turn *= 2 * M_PI / 360;
    if (turn) {
      rotationY(&(ui->model_view->object), turn);
      ui->model_view->update();
    }
  }
}

void MainWindow::on_zTurnButton_clicked() {
  if (ui->model_view->isLoaded) {
    double turn = ui->zTurnInput->value();
    if (ui->radioButton_2->isChecked()) turn *= 2 * M_PI / 360;
    if (turn) {
      rotationZ(&(ui->model_view->object), turn);
      ui->model_view->update();
    }
  }
}

void MainWindow::on_shiftButton_clicked() {
  if (ui->model_view->isLoaded) {
    shift(&(ui->model_view->object), ui->xShiftInput->value(),
          ui->yShiftInput->value(), ui->zShiftInput->value());
    ui->model_view->update();
  }
}

void MainWindow::on_scaleButton_clicked() {
  if (ui->model_view->isLoaded && ui->scaleInput->value() != 0) {
    scaling(&(ui->model_view->object), ui->scaleInput->value());
    ui->model_view->update();
  }
}

void MainWindow::on_resizeButton_clicked() {
  if (ui->model_view->isLoaded) {
    for (int i = 0; i < ui->model_view->object.point.columns; i++) {
      for (int j = 0; j < 3; j++) {
        ui->model_view->object.point.matrix[j][i] =
            ui->model_view->backupPoint->matrix[j][i];
      }
    }
    ui->model_view->update();
  }
}

void MainWindow::on_snapshotButton_clicked() {
  if (ui->model_view->isLoaded) {
    QString fileName = QFileDialog::getSaveFileName(
        this, "Save as...", "snapshot", "BMP (*.bmp);;JPG (*.jpg)");
    if (!fileName.isEmpty()) {
      if (!fileName.endsWith(".jpg") &&
          ui->comboBox_fileFormat->currentText() == "jpg") {
        fileName += ".jpg";
      } else if (!fileName.endsWith(".jpg") &&
                 ui->comboBox_fileFormat->currentText() == "bmp") {
        fileName += ".bmp";
      }

      this->ui->model_view->grab().save(fileName);
    }
  }
}

void MainWindow::on_pushButton_OpenFile_clicked() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open Model"), "",
                                                  tr("Model Files (*.obj)"));
  if (fileName.length() != 0) {
    if (ui->model_view->isLoaded) free_model(&ui->model_view->object);
    ui->model_view->isLoaded = 0;
    int status = ui->model_view->loadModel(fileName);
    if (!status) {
      ui->model_view->isLoaded = 1;
      QString name =
          fileName.right(fileName.size() - fileName.lastIndexOf("/") - 1);
      ui->textEdit_modelInfo->setText(
          "file: " + name + "\ncount of vertexes: " +
          QString::number(ui->model_view->object.point.columns - 4) +
          "\ncount of edges: " +
          QString::number(get_count_of_edges(&ui->model_view->object)));
    } else {
      ui->textEdit_modelInfo->setText("Not Loaded");
    }

    ui->model_view->update();
  }
}

void MainWindow::on_comboBox_projectionType_currentIndexChanged(int index) {
  ui->model_view->options.projectionType = index;
  ui->model_view->update();
}

void MainWindow::on_pointSizeInput_valueChanged(int arg1) {
  ui->model_view->options.pointSize = arg1;
  ui->model_view->update();
}

void MainWindow::on_vertexType_currentIndexChanged(int index) {
  if (index == 0) {
    ui->model_view->options.pointType = 0;
  }
  if (index == 1) {
    ui->model_view->options.pointType = 1;
  }
  if (index == 2) {
    ui->model_view->options.pointType = 2;
  }
  ui->model_view->update();
}

void MainWindow::on_edgeSize_valueChanged(int arg1) {
  ui->model_view->options.edgeSize = arg1;
  ui->model_view->update();
}

void MainWindow::on_comboBox_edgesType_currentIndexChanged(int index) {
  if (index == 0) {
    ui->model_view->options.edgeType = 0;
  }
  if (index == 1) {
    ui->model_view->options.edgeType = 1;
  }
  ui->model_view->update();
}

void MainWindow::on_pushButton_backColor_clicked() {
  QColor color = QColorDialog::getColor();
  float r, g, b;
  color.getRgbF(&r, &g, &b);
  if (color.isValid()) {
    ui->model_view->options.backColor[0] = r;
    ui->model_view->options.backColor[1] = g;
    ui->model_view->options.backColor[2] = b;
    ui->model_view->update();
  }
}

void MainWindow::on_pushButton_vertexColor_clicked() {
  QColor color = QColorDialog::getColor();
  float r, g, b;
  color.getRgbF(&r, &g, &b);
  if (color.isValid()) {
    ui->model_view->options.pointColor[0] = r;
    ui->model_view->options.pointColor[1] = g;
    ui->model_view->options.pointColor[2] = b;
    ui->model_view->update();
  }
}

void MainWindow::on_pushButton_edgeColor_clicked() {
  QColor color = QColorDialog::getColor();
  float r, g, b;
  color.getRgbF(&r, &g, &b);
  if (color.isValid()) {
    ui->model_view->options.edgeColor[0] = r;
    ui->model_view->options.edgeColor[1] = g;
    ui->model_view->options.edgeColor[2] = b;
    ui->model_view->update();
  }
}

void MainWindow::on_radioButton_clicked() {
  ui->xTurnInput->setRange(-7.0, 7.0);
  ui->xTurnInput->setSingleStep(0.1);
  ui->xTurnInput->setDecimals(2);
  ui->yTurnInput->setRange(-7.0, 7.0);
  ui->yTurnInput->setSingleStep(0.1);
  ui->yTurnInput->setDecimals(2);
  ui->zTurnInput->setRange(-7.0, 7.0);
  ui->zTurnInput->setSingleStep(0.1);
  ui->zTurnInput->setDecimals(2);
}

void MainWindow::on_radioButton_2_clicked() {
  ui->xTurnInput->setRange(-360.0, 360.0);
  ui->xTurnInput->setSingleStep(5.0);
  ui->xTurnInput->setDecimals(0);
  ui->yTurnInput->setRange(-360.0, 360.0);
  ui->yTurnInput->setSingleStep(5.0);
  ui->yTurnInput->setDecimals(0);
  ui->zTurnInput->setRange(-360.0, 360.0);
  ui->zTurnInput->setSingleStep(5.0);
  ui->zTurnInput->setDecimals(0);
}

void MainWindow::on_pushButton_saveOptions_clicked() {
  saveOptions("settings.txt", ui->model_view->options);
}

void MainWindow::on_doubleSpinBox_focus_dist_valueChanged(double arg1) {
  ui->model_view->focus_dist = arg1;
  ui->model_view->update();
}

void MainWindow::on_scaleInputSlider_valueChanged(int value) {
  ui->scaleInput->setValue((double)value / 10.0);
}

void MainWindow::on_restoreOptionsButton_clicked() {
  ui->model_view->options.pointType = 0;
  ui->vertexType->setCurrentIndex(0);
  ui->model_view->options.pointSize = 5;
  ui->pointSizeInput->setValue(5);
  ui->model_view->options.pointColor[0] = 1;
  ui->model_view->options.pointColor[1] = 1;
  ui->model_view->options.pointColor[2] = 1;
  ui->model_view->options.projectionType = 0;
  ui->comboBox_projectionType->setCurrentIndex(0);
  ui->model_view->options.edgeColor[0] = 0.1;
  ui->model_view->options.edgeColor[1] = 0.1;
  ui->model_view->options.edgeColor[2] = 1;
  ui->model_view->options.backColor[0] = 0.5;
  ui->model_view->options.backColor[1] = 0.5;
  ui->model_view->options.backColor[2] = 0.5;
  ui->model_view->options.edgeSize = 1;
  ui->edgeSize->setValue(1);
  ui->model_view->options.edgeType = 0;
  ui->comboBox_edgesType->setCurrentIndex(0);

  ui->model_view->update();
}

void MainWindow::on_gifMakeButton_clicked() {
  timer->start(100);
  timerRun();
  count = 0.0;
}

void MainWindow::timerRun() {
  if (count <= 5.0) {
    gif.push_back(ui->model_view->grab().toImage());
    count += 0.1;
  } else {
    makeGIF();
    timer->stop();
  }
}

void MainWindow::makeGIF() {
  QString gif_name =
      QFileDialog::getSaveFileName(this, "Save gif", "", "*.gif");
  QGifImage gif_image(QSize(640, 480));
  gif_image.setDefaultDelay(100);

  for (QVector<QImage>::Iterator screen = gif.begin(); screen != gif.end();
       ++screen) {
    gif_image.addFrame(*screen);
  }
  if (!gif_name.isEmpty()) {
    if (!gif_name.endsWith(".gif")) gif_name += ".gif";
    gif_image.save(gif_name);
  }
  gif.clear();
  count = 0.0;
}
