#ifndef _OPENGL_SHADER_CLASS_H_
#define _OPENGL_SHADER_CLASS_H_

#include <glad/glad.h>
#include <string>
#include <string_view>

namespace utils
{
class Shader
{
public:
    explicit Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

    void useShaderProgram();
    GLuint getShaderProgramId();

    void setBoolUniform(const std::string& name, const GLboolean& value);
    void setIntUniform(const std::string& name, const GLint& value);
    void setFloatUniform(const std::string& name, const GLfloat& value);
    void setMatrix4fUniform(const std::string& name, const GLfloat* value);

private:
    void checkShaderCompileError(GLuint shader_id, const std::string_view error_type);

private:
    GLuint shader_program_id_;
    static constexpr std::string_view kProgramError = "PROGRAM";
    static constexpr std::string_view kVertexError = "VERTEX";
    static constexpr std::string_view kFragmentError = "FRAGMENT";
};
}  // namespace utils

#endif