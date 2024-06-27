#include <QtCore/qobject.h>
#include <QtWidgets/QApplication>
#include "dopenglwidget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    auto* d_widget = new DzhOpenGLWidget();
    d_widget->show();
    app.exec();
}