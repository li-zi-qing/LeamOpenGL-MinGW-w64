#ifndef OPENGL_TOOLS_H
#define OPENGL_TOOLS_H

#include <string>
#include <glad/gl.h>
#include <glm/glm.hpp>

namespace OpenGLTools
{
    class Shader
    {
    public:
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
        ~Shader();
        Shader& use();
        Shader& setBool(const std::string& name, GLboolean value);
        Shader& setInt(const std::string& name, GLint value);
        Shader& setFloat(const std::string& name, GLfloat value);
        Shader& setVec2(const std::string& name, const glm::vec2& value);
        Shader& setVec2(const std::string& name, GLfloat x, GLfloat y);
        Shader& setVec3(const std::string& name, const glm::vec3& value);
        Shader& setVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z);
        Shader& setVec4(const std::string& name, const glm::vec4& value);
        Shader& setVec4(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
        Shader& setMat2(const std::string& name, const glm::mat2& mat);
        Shader& setMat3(const std::string& name, const glm::mat3& mat);
        Shader& setMat4(const std::string& name, const glm::mat4& mat);

    private:
        GLuint ID;
    };
}
#endif //OPENGL_TOOLS_H
