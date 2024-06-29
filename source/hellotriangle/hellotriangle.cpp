#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

void frameBufferSizeCb(GLFWwindow* window, GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
}

void processInput(GLFWwindow* window)
{
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void render()
{
    // status set
    glClearColor(0.2f, 0.3f, 0.3f, 0.3f);
    // status use
    glClear(GL_COLOR_BUFFER_BIT);
}

const GLchar* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const GLchar* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

void init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void configShaderProgram(GLuint& vertex_shader, GLuint& frag_shader)
{
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertex_shader);

    GLint success;
    GLint log_size = 512;
    GLchar info_log[log_size];
    if (glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success); !success)
    {
        glGetShaderInfoLog(vertex_shader, log_size, nullptr, info_log);
        std::cout << "Error: Shader Vertex Compilation Failed" << std::endl << info_log << std::endl;
    }

    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(frag_shader);
    if (glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success); !success)
    {
        glGetShaderInfoLog(frag_shader, log_size, nullptr, info_log);
        std::cout << "Error: Shader Fragment Compilation Failed" << std::endl << info_log << std::endl;
    }
}

void linkShaderProgram(GLuint& shader_program, GLuint& vertex_shader, GLuint& frag_shader)
{
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, frag_shader);
    glLinkProgram(shader_program);

    GLint success;
    GLint log_size = 512;
    GLchar info_log[log_size];
    if (glGetProgramiv(shader_program, GL_LINK_STATUS, &success); !success)
    {
        glGetProgramInfoLog(shader_program, log_size, nullptr, info_log);
        std::cout << "Error: Shader Program Link Failed" << std::endl << info_log << std::endl;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);
}

void configAndBindObject(GLuint& vao, GLuint& vbo, GLuint& ebo)
{
    GLfloat triangle_vertices[] = {
        -0.5f, -0.5f, 0.0f,  // left
        0.5f,  -0.5f, 0.0f,  // right
        0.0f,  0.5f,  0.0f   // top
    };

    float rectangle_vertices[] = {
        0.5f,  0.5f,  0.0f,  // top right
        0.5f,  -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f, 0.5f,  0.0f   // top left
    };
    unsigned int rectangle_indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle_vertices), rectangle_vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangle_indices), rectangle_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

int main()
{
    init();

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Triangle", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCb);

    if (auto proc_address = (GLADloadproc)glfwGetProcAddress; !gladLoadGLLoader(proc_address))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    GLuint vertex_shader;
    GLuint frag_shader;
    configShaderProgram(vertex_shader, frag_shader);

    GLuint shader_program;
    linkShaderProgram(shader_program, vertex_shader, frag_shader);

    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    configAndBindObject(vao, vbo, ebo);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        render();

        glUseProgram(shader_program);
        glBindVertexArray(vao);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shader_program);

    glfwTerminate();
    return 0;
}