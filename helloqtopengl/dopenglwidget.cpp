#include "dopenglwidget.h"

DOpenGLWidget::DOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

void DOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // Define vertices for a triangle
    GLfloat vertices[] = {0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f};

    // Create and bind a vertex array object
    vao.create();
    vao.bind();

    // Create and bind a vertex buffer object
    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, 9 * sizeof(float));

    // Create a shader program
    program.create();
    program.addShaderFromSourceCode(QOpenGLShader::Vertex,
                                    "attribute vec3 position; \
                                          void main() { \
                                              gl_Position = vec4(position, 1.0); \
                                          }");
    program.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                    "void main() { \
                                              gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); \
                                          }");
    program.link();
}

void DOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void DOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    program.bind();

    vbo.bind();
    program.enableAttributeArray(0);
    program.setAttributeBuffer(0, GL_FLOAT, 0, 3);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    vbo.release();
    program.release();
}