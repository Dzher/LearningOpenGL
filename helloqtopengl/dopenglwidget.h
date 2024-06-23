#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLFunctions_4_5_Core>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QWidget>

class DzhOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    DzhOpenGLWidget(QWidget* parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
};