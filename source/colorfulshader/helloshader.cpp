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
    glClearColor(0.2f, 0.3f, 0.3f, 0.3f);
    glClear(GL_COLOR_BUFFER_BIT);
}

const GLchar* greenVertexShaderSource =
    "#version 450 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos, 1.0);\n "
    "}\0 ";
const char* greenFragmentShaderSource =
    "#version 450 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 greenColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = greenColor;\n"
    "}\n\0";

const GLchar* colorfulVertexShaderSource =
    "#version 450 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 colorfulColor;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos, 1.0);\n "
    "    colorfulColor = aColor;\n"
    "}\0 ";
const char* colorfulFragmentShaderSource =
    "#version 450 core\n"
    "out vec4 FragColor;\n"
    "in vec3 colorfulColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(colorfulColor, 1.0f);\n"
    "}\n\0";

void init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void configShaderProgram(GLuint& vertex_shader, GLuint& frag_shader, bool colorful = false)
{
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    colorful ? glShaderSource(vertex_shader, 1, &colorfulVertexShaderSource, nullptr)
             : glShaderSource(vertex_shader, 1, &greenVertexShaderSource, nullptr);
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
    colorful ? glShaderSource(frag_shader, 1, &colorfulFragmentShaderSource, nullptr)
             : glShaderSource(frag_shader, 1, &greenFragmentShaderSource, nullptr);
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

void configAndBindObject(GLuint& vao, GLuint& vbo)
{
    GLfloat triangle_vertices[] = {
        -0.5f, -0.5f, 0.0f, /*left Point*/ 1.0f,  0.0f, 0.0f, /*left Color*/
        0.5f,  -0.5f, 0.0f, /*right Point*/ 0.0f, 1.0f, 0.0f, /*right Color*/
        0.0f,  0.5f,  0.0f, /*top Point*/ 0.0f,   0.0f, 1.0f  /*top Color*/
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

    // Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(0));
    glEnableVertexAttribArray(0);

    // Color Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void greenShader(GLuint& shader_program)
{
    double current_time = glfwGetTime();
    float color_value = std::sin(current_time) / 2.0 + 0.5;
    int vertex_color_location = glGetUniformLocation(shader_program, "greenColor");
    glUniform4f(vertex_color_location, 0.0f, color_value, 0.0f, 1.0f);
}

int main(int argc, char* argv[])
{
    init();

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Shader", nullptr, nullptr);
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

    bool colorful = false;
    if (argc > 1)
    {
        colorful = argv[1];
    }

    GLuint vertex_shader;
    GLuint frag_shader;
    configShaderProgram(vertex_shader, frag_shader, colorful);

    GLuint shader_program;
    linkShaderProgram(shader_program, vertex_shader, frag_shader);

    GLuint vao;
    GLuint vbo;
    configAndBindObject(vao, vbo);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        render();

        glUseProgram(shader_program);
        glBindVertexArray(vao);
        if (!colorful)
        {
            greenShader(shader_program);
        }
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader_program);

    glfwTerminate();
    return 0;
}