#include "shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "glm/gtc/type_ptr.hpp"
#include "utils/pathhelper/pathhelper.h"

using namespace utils;

Shader::Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{
    GLuint vertex_shader_id = initVertexShader(vertex_shader_path);
    GLuint fragment_shader_id = initFragmentShader(fragment_shader_path);

    shader_program_id_ = glCreateProgram();
    glAttachShader(shader_program_id_, vertex_shader_id);
    glAttachShader(shader_program_id_, fragment_shader_id);
    glLinkProgram(shader_program_id_);
    checkShaderCompileError(shader_program_id_, kProgramError);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
}

Shader::Shader(const std::string& vertex_shader_path, const std::string& geometry_shader_path,
               const std::string& fragment_shader_path)
{
    GLuint vertex_shader_id = initVertexShader(vertex_shader_path);
    GLuint geometry_shader_id = initGeometryShader(geometry_shader_path);
    GLuint fragment_shader_id = initFragmentShader(fragment_shader_path);

    shader_program_id_ = glCreateProgram();
    glAttachShader(shader_program_id_, vertex_shader_id);
    glAttachShader(shader_program_id_, geometry_shader_id);
    glAttachShader(shader_program_id_, fragment_shader_id);
    glLinkProgram(shader_program_id_);
    checkShaderCompileError(shader_program_id_, kProgramError);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(geometry_shader_id);
    glDeleteShader(fragment_shader_id);
}

GLuint Shader::initVertexShader(const std::string& path)
{
    std::string vertex_code;
    std::ifstream vertex_file;
    vertex_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vertex_file.open(utils::PathHelper::getShaderPath(path));
        std::stringstream vertex_buff;
        vertex_buff << vertex_file.rdbuf();
        vertex_code = vertex_buff.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << kVertexError << " "
                  << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    const GLchar* vertex_code_str = vertex_code.c_str();
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_id, 1, &vertex_code_str, nullptr);
    glCompileShader(vertex_shader_id);
    checkShaderCompileError(vertex_shader_id, kVertexError);

    return vertex_shader_id;
}

GLuint Shader::initFragmentShader(const std::string& path)
{
    std::string fragment_code;
    std::ifstream fragment_file;

    fragment_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {

        fragment_file.open(utils::PathHelper::getShaderPath(path));
        std::stringstream fragment_buff;
        fragment_buff << fragment_file.rdbuf();
        fragment_code = fragment_buff.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << kFragmentError << " "
                  << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    const GLchar* fragment_code_str = fragment_code.c_str();
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_id, 1, &fragment_code_str, nullptr);
    glCompileShader(fragment_shader_id);
    checkShaderCompileError(fragment_shader_id, kFragmentError);

    return fragment_shader_id;
}

GLuint Shader::initGeometryShader(const std::string& path)
{
    std::string geometry_code;
    std::ifstream geometry_file;

    geometry_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {

        geometry_file.open(utils::PathHelper::getShaderPath(path));
        std::stringstream geometry_buff;
        geometry_buff << geometry_file.rdbuf();
        geometry_code = geometry_buff.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << kGeometryError << " "
                  << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    const GLchar* geometry_code_str = geometry_code.c_str();
    GLuint geometry_shader_id = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry_shader_id, 1, &geometry_code_str, nullptr);
    glCompileShader(geometry_shader_id);
    checkShaderCompileError(geometry_shader_id, kGeometryError);

    return geometry_shader_id;
}

void Shader::useShaderProgram()
{
    glUseProgram(shader_program_id_);
}

GLuint Shader::getShaderProgramId()
{
    return shader_program_id_;
}

void Shader::setBoolUniform(const std::string& name, const GLboolean& value)
{
    glUniform1i(glGetUniformLocation(shader_program_id_, name.data()), value);
}

void Shader::setIntUniform(const std::string& name, const GLint& value)
{
    glUniform1i(glGetUniformLocation(shader_program_id_, name.data()), value);
}

void Shader::setFloatUniform(const std::string& name, const GLfloat& value)
{
    glUniform1f(glGetUniformLocation(shader_program_id_, name.data()), value);
}

void Shader::setVec3Uniform(const std::string& name, const glm::vec3& value)
{
    auto r = value.r;
    auto g = value.g;
    auto b = value.b;
    glUniform3f(glGetUniformLocation(shader_program_id_, name.data()), r, g, b);
}

void Shader::setVec3Uniform(const std::string& name, const GLfloat* value)
{
    auto r = value[0];
    auto g = value[1];
    auto b = value[2];
    glUniform3f(glGetUniformLocation(shader_program_id_, name.data()), r, g, b);
}

void Shader::setVec3Uniform(const std::string& name, const GLfloat& r, const GLfloat& g, const GLfloat& b)
{
    glUniform3f(glGetUniformLocation(shader_program_id_, name.data()), r, g, b);
}

void Shader::setMatrix4fUniform(const std::string& name, const GLfloat* value)
{
    glUniformMatrix4fv(glGetUniformLocation(shader_program_id_, name.data()), 1, GL_FALSE, value);
}

void Shader::setMatrix4fUniform(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(shader_program_id_, name.data()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::checkShaderCompileError(GLuint shader_id, const std::string_view error_type)
{
    int success;
    char info_log[512];
    if (error_type == kProgramError)
    {
        glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader_id, 1024, NULL, info_log);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << error_type << std::endl << info_log << std::endl;
        }
    }
    else
    {
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader_id, 1024, NULL, info_log);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << error_type << std::endl
                      << info_log << std::endl;
        }
    }
}