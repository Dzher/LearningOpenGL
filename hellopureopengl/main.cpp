#include <QtCore/qobject.h>
#include <QtWidgets/QApplication>
#include "dpureopengl.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    auto* d_widget = new DzhPureOpenGL();
    d_widget->show();
    app.exec();
}