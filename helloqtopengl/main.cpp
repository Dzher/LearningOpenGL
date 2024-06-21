#include "dopenglwidget.h"
#include <QtCore/qobject.h>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  auto *d_widget = new DOpenGLWidget();
  d_widget->show();
  app.exec();
}