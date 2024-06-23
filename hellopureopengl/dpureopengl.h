#include <GL/gl.h>
#include <QtGui/QOpenGLFunctions_4_5_Core>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QWidget>

class DzhPureOpenGL : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    DzhPureOpenGL(QWidget* parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    GLuint vbo_;
    GLuint vao_;
};