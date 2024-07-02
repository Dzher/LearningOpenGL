#include "utils/common/common.h"
#include "utils/pathhelper/pathhelper.h"
#include "utils/shader/shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void configAndBindObjects(GLuint& vao, GLuint& vbo, GLuint& ebo)
{
    float vertices[] = {
        // positions        // texture coords
        0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // top right
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // bottom left
        -0.5f, 0.5f,  0.0f, 0.0f, 1.0f   // top left
    };
    unsigned int indices[] = {
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int main()
{
    GLFWwindow* context = Utils::CommonFunc::initContext("Hello Transform");
    Utils::Shader shader_program(Utils::PathHelper::getShaderPath("transform.vert"),
                                 Utils::PathHelper::getShaderPath("transform.frag"));

    GLuint vao, vbo, ebo;
    configAndBindObjects(vao, vbo, ebo);

    GLuint texture_0;
    GLuint texture_1;
    Utils::CommonFunc::configAndBindTexture(texture_0, "girl.jpg");
    Utils::CommonFunc::configAndBindTexture(texture_1, "girl.jpg", true);

    shader_program.useShaderProgram();
    shader_program.setIntUniform("texture_0", 0);
    shader_program.setIntUniform("texture_1", 1);

    while (!glfwWindowShouldClose(context))
    {
        Utils::CommonFunc::render();
        Utils::CommonFunc::processInput(context);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture_1);

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        // get matrix's uniform location and set matrix
        shader_program.useShaderProgram();
        GLuint transform_loc = glGetUniformLocation(shader_program.getShaderProgramId(), "transform");
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(context);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glfwTerminate();
    return 0;
}