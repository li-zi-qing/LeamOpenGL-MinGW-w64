#ifndef OPENGL_TOOLS_H
#define OPENGL_TOOLS_H

#include <string>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <packGlm.h>

namespace OpenGLTools
{
    class Shader
    {
    public:
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

        ~Shader();

        Shader& use();

        Shader& setBool(const std::string& name, GLboolean value);

        Shader& setBool(const packGlm<GLboolean>& value);

        Shader& setInt(const std::string& name, GLint value);

        Shader& setInt(const packGlm<int>& value);

        Shader& setFloat(const std::string& name, GLfloat value);

        Shader& setFloat(const packGlm<float>& value);

        Shader& setVec2(const packGlm<glm::vec2>& value);

        Shader& setVec2(const std::string& name, const glm::vec2& value);

        Shader& setVec2(const std::string& name, GLfloat x, GLfloat y);

        Shader& setVec3(const packGlm<glm::vec3>& value);

        Shader& setVec3(const std::string& name, const glm::vec3& value);

        Shader& setVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z);

        Shader& setVec4(const packGlm<glm::vec4>& value);

        Shader& setVec4(const std::string& name, const glm::vec4& value);

        Shader& setVec4(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

        Shader& setMat2(const packGlm<glm::mat2>& value);

        Shader& setMat2(const std::string& name, const glm::mat2& mat);

        Shader& setMat3(const packGlm<glm::mat3>& value);

        Shader& setMat3(const std::string& name, const glm::mat3& mat);

        Shader& setMat4(const packGlm<glm::mat4>& value);

        Shader& setMat4(const std::string& name, const glm::mat4& mat);

    private:
        GLuint ID;
    };

    enum Direction
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    class Camera
    {
    public:
        explicit Camera(
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            GLfloat yaw = -90.0f,
            GLfloat pitch = 0.0f
        );

        Camera(
            GLfloat posX,
            GLfloat posY,
            GLfloat posZ,
            GLfloat upX,
            GLfloat upY,
            GLfloat upZ,
            GLfloat yaw,
            GLfloat pitch
        );


        GLvoid processKeyboard(Direction direction, GLfloat deltaTime);

        GLvoid processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = GL_TRUE);

        GLvoid processMouseScroll(GLfloat yOffset);

        [[nodiscard]] GLfloat getYaw() const;

        [[nodiscard]] GLfloat getPitch() const;

        [[nodiscard]] GLfloat getSensitivity() const;

        [[nodiscard]] GLfloat getZoom() const;

        [[nodiscard]] glm::vec3 getPosition() const;

        [[nodiscard]] glm::vec3 getFront() const;

        [[nodiscard]] glm::vec3 getUp() const;

        [[nodiscard]] glm::vec3 getRight() const;

        [[nodiscard]] glm::mat4 getViewMatrix() const;

    private:
        glm::vec3 position;
        glm::vec3 front{0.0f, 0.0f, -1.0f};
        glm::vec3 up;
        glm::vec3 right;
        GLfloat yaw;
        GLfloat pitch;
        GLfloat speed{2.5f};
        GLfloat sensitivity{0.1f};
        GLfloat zoom{45.0f};

        GLvoid updateCameraVectors();
    };

    class Init
    {
    public:
        Init& setScreenWidth(GLuint argScreenWidth);

        [[nodiscard]] GLuint getScreenWidth() const;

        Init& setScreenHeight(GLuint argScreenHeight);

        [[nodiscard]] GLuint getScreenHeight() const;

        static Init& getInstance();

        Init& setCamera(const Camera& argCamera);

        [[nodiscard]] Camera getCamera() const;

        Init& setLastX(GLfloat argLastX);

        [[nodiscard]] GLfloat getLastX() const;

        Init& setLastY(GLfloat argLastY);

        [[nodiscard]] GLfloat getLastY() const;

        Init& setFirstMouse(GLboolean argFirstMouse);

        [[nodiscard]] GLboolean getFirstMouse() const;

        Init& setDeltaTime(GLfloat argDeltaTime);

        [[nodiscard]] GLfloat getDeltaTime() const;

        Init& setLastFrame(GLfloat argLastFrame);

        [[nodiscard]] GLfloat getLastFrame() const;

        [[nodiscard]] GLFWwindow* getWindow() const;

        Init& setTitle(const GLchar* argTitle);

        GLboolean builder();

    private:
        GLuint screenWidth{0};
        GLuint screenHeight{0};
        Camera camera{Camera()};
        GLfloat lastX{0};
        GLfloat lastY{0};
        GLboolean firstMouse{GL_TRUE};
        GLfloat deltaTime{0.0f};
        GLfloat lastFrame{0.0f};
        GLFWwindow* window{nullptr};
        const GLchar* title{"OpenGL"};

        explicit Init(
            GLuint screenWidth,
            GLuint screenHeight,
            Camera camera,
            GLfloat lastX,
            GLfloat lastY,
            GLboolean firstMouse,
            GLfloat deltaTime,
            GLfloat lastFrame,
            const GLchar* title
        );

        Init() = default;

        ~Init();
    };


    GLvoid framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height);

    GLvoid mouse_callback(GLFWwindow* window, GLdouble xPos, GLdouble yPos);

    GLvoid scroll_callback(GLFWwindow* window, GLdouble xOffset, GLdouble yOffset);

    GLvoid processInput(GLFWwindow* window);

    GLuint loadTexture(GLchar const* path);
}

#endif //OPENGL_TOOLS_H
