#include <OpenGLTools.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace OpenGLTools;

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch ([[maybe_unused]] std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertex);
    glAttachShader(this->ID, fragment);
    glLinkProgram(this->ID);
    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->ID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{
    glDeleteProgram(this->ID);
}

Shader& Shader::use()
{
    glUseProgram(this->ID);
    return *this;
}

Shader& Shader::setBool(const std::string& name, const GLboolean value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<GLint>(value));
    return *this;
}

Shader& Shader::setBool(const packGlm<GLboolean>& value)
{
    glUniform1i(glGetUniformLocation(ID, static_cast<std::string>(value).c_str()), static_cast<GLboolean>(value));
    return *this;
}

Shader& Shader::setInt(const packGlm<int>& value)
{
    glUniform1i(glGetUniformLocation(ID, static_cast<std::string>(value).c_str()), static_cast<GLint>(value));
    return *this;
}

Shader& Shader::setFloat(const packGlm<float>& value)
{
    glUniform1f(glGetUniformLocation(ID, static_cast<std::string>(value).c_str()), static_cast<GLfloat>(value));
    return *this;
}

Shader& Shader::setVec2(const packGlm<glm::vec2>& value)
{
    glUniform2fv(glGetUniformLocation(ID, static_cast<std::string>(value).c_str()), 1,
                 &static_cast<glm::vec2>(value)[0]);
    return *this;
}

Shader& Shader::setVec4(const packGlm<glm::vec4>& value)
{
    glUniform4fv(glGetUniformLocation(ID, static_cast<std::string>(value).c_str()), 1,
                 &static_cast<glm::vec4>(value)[0]);
    return *this;
}

Shader& Shader::setVec3(const packGlm<glm::vec3>& value)
{
    glUniform3fv(glGetUniformLocation(ID, static_cast<std::string>(value).c_str()), 1,
                 &static_cast<glm::vec3>(value)[0]);
    return *this;
}

Shader& Shader::setInt(const std::string& name, const GLint value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    return *this;
}

Shader& Shader::setFloat(const std::string& name, const GLfloat value)
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    return *this;
}

Shader& Shader::setVec2(const std::string& name, const glm::vec2& value)
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    return *this;
}

Shader& Shader::setVec2(const std::string& name, const GLfloat x, const GLfloat y)
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    return *this;
}

Shader& Shader::setVec3(const std::string& name, const glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    return *this;
}

Shader& Shader::setVec3(const std::string& name, const GLfloat x, const GLfloat y, const GLfloat z)
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    return *this;
}

Shader& Shader::setVec4(const std::string& name, const glm::vec4& value)
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    return *this;
}

Shader& Shader::setVec4(
    const std::string& name, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w
)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    return *this;
}

Shader& Shader::setMat2(const packGlm<glm::mat2>& value)
{
    glUniformMatrix2fv(glGetUniformLocation(ID, static_cast<std::string>(value).c_str()), 1, GL_FALSE,
                       &static_cast<glm::mat2>(value)[0][0]);
    return *this;
}

Shader& Shader::setMat3(const packGlm<glm::mat3>& value)
{
    glUniformMatrix3fv(glGetUniformLocation(ID, static_cast<std::string>(value).c_str()), 1, GL_FALSE,
                       &static_cast<glm::mat3>(value)[0][0]);
    return *this;
}

Shader& Shader::setMat4(const packGlm<glm::mat4>& value)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, static_cast<std::string>(value).c_str()), 1, GL_FALSE,
                       &static_cast<glm::mat4>(value)[0][0]);
    return *this;
}

Shader& Shader::setMat2(const std::string& name, const glm::mat2& mat)
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    return *this;
}

Shader& Shader::setMat3(const std::string& name, const glm::mat3& mat)
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    return *this;
}

Shader& Shader::setMat4(const std::string& name, const glm::mat4& mat)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    return *this;
}
