#include "dpureopengl.h"
#include <GL/gl.h>
#include <qopenglext.h>

DzhPureOpenGL::DzhPureOpenGL(QWidget* parent) : QOpenGLWidget(parent) {}

void DzhPureOpenGL::initializeGL()
{
    initializeOpenGLFunctions();

    // Define vertices for a triangle
    GLfloat vertices[] = {0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f};

    // Create and bind a vertex array object
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);

    // Create and bind a vertex buffer object
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    // make buffer data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // how to use the buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void DzhPureOpenGL::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void DzhPureOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}