#ifndef OPENGL_TOOLS_H
#define OPENGL_TOOLS_H
#include <string>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <packGlm.h>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

namespace OpenGLTools {
    class Shader {
        public:

            /**
             * Shader 类的有参构造函数.
             * @param vertexPath 顶点着色器文件路径.
             * @param fragmentPath 片元着色器文件路径.
             */
            Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

            /**
             * Shader 类的析构函数.
             */
            ~Shader();


            /**
             * 激活当前 Shader 类的着色器程序.
             * @return 当前 Shader 类的引用.
             */
            Shader& use();


            /**
             * 设置 bool 类型的 Uniform 值.
             * @param name Uniform 的名称.
             * @param value Uniform 的值.
             * @return 当前 Shader 类的引用.
             */
            Shader& setBool(const std::string& name, GLboolean value);

            /**
             * 设置 bool 类型的 Uniform 值.
             * @param value packGlm<bool> 的引用.
             * @return 当前 Shader 类的引用.
             */
            Shader& setBool(const packGlm<GLboolean>& value);


            /**
             * 设置 int 类型的 Uniform 值.
             * @param name Uniform 的名称.
             * @param value Uniform 的值.
             * @return 当前 Shader 类的引用.
             */
            Shader& setInt(const std::string& name, GLint value);

            /**
             * 设置 int 类型的 Uniform 值.
             * @param value packGlm<int> 的引用.
             * @return 当前 Shader 类的引用.
             */
            Shader& setInt(const packGlm<int>& value);


            /**
             * 设置 float 类型的 Uniform 值.
             * @param name Uniform 的名称.
             * @param value Uniform 的值.
             * @return 当前 Shader 类的引用.
             */
            Shader& setFloat(const std::string& name, GLfloat value);

            /**
             * 设置 float 类型的 Uniform 值.
             * @param value packGlm<float> 的引用.
             * @return 当前 Shader 类的引用.
             */
            Shader& setFloat(const packGlm<float>& value);

            /**
             * 设置 glm::vec2 类型的 Uniform 值.
             * @param value packGlm<glm::vec2> 的引用.
             * @return 当前 Shader 类的引用.
             */
            Shader& setVec2(const packGlm<glm::vec2>& value);

            /**
            * 设置 glm::vec2 类型的 Uniform 值.
            * @param name Uniform 的名称.
            * @param value Uniform 的值.
            * @return 当前 Shader 类的引用.
            */
            Shader& setVec2(const std::string& name, const glm::vec2& value);


            /**
             * 设置 glm::vec2 类型的 Uniform 值.
             * @param name Uniform 的名称.
             * @param x glm::vec2 的 x.
             * @param y glm::vec2 的 y.
             * @return 当前 Shader 类的引用.
             */
            Shader& setVec2(const std::string& name, GLfloat x, GLfloat y);

            /**
             * 设置 glm::vec3 类型的 Uniform 值.
             * @param value packGlm<glm::vec3> 的引用.
             * @return 当前 Shader 类的引用.
             */
            Shader& setVec3(const packGlm<glm::vec3>& value);

            /**
            * 设置 glm::vec3 类型的 Uniform 值.
            * @param name Uniform 的名称.
            * @param value Uniform 的值.
            * @return 当前 Shader 类的引用.
            */
            Shader& setVec3(const std::string& name, const glm::vec3& value);


            /**
             * 设置 glm::vec3 类型的 Uniform 值.
             * @param name Uniform 的名称.
             * @param x glm::vec3 的 x.
             * @param y glm::vec3 的 y.
             * @param z glm::vec3 的 z.
             * @return 当前 Shader 类的引用.
             */
            Shader& setVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z);

            /**
             * 设置 glm::vec4 类型的 Uniform 值.
             * @param value packGlm<glm::vec4> 的引用.
             * @return 当前 Shader 类的引用.
             */
            Shader& setVec4(const packGlm<glm::vec4>& value);

            /**
            * 设置 glm::vec4 类型的 Uniform 值.
            * @param name Uniform 的名称.
            * @param value Uniform 的值.
            * @return 当前 Shader 类的引用.
            */
            Shader& setVec4(const std::string& name, const glm::vec4& value);


            /**
             * 设置 glm::vec4 类型的 Uniform 值.
             * @param name Uniform 的名称.
             * @param x glm::vec4 的 x.
             * @param y glm::vec4 的 y.
             * @param z glm::vec4 的 z.
             * @param w glm::vec4 的 w.
             * @return 当前 Shader 类的引用.
             */
            Shader& setVec4(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

            /**
             * 设置 glm::mat2 类型的 Uniform 值.
             * @param value packGlm<glm::mat2> 的引用.
             * @return 当前 Shader 类的引用.
             */
            Shader& setMat2(const packGlm<glm::mat2>& value);

            /**
            * 设置 glm::mat2 类型的 Uniform 值.
            * @param name Uniform 的名称.
            * @param mat Uniform 的值.
            * @return 当前 Shader 类的引用.
            */
            Shader& setMat2(const std::string& name, const glm::mat2& mat);

            /**
             * 设置 glm::mat3 类型的 Uniform 值.
             * @param value packGlm<glm::mat3> 的引用.
             * @return 当前 Shader 类的引用.
             */
            Shader& setMat3(const packGlm<glm::mat3>& value);

            /**
            * 设置 glm::mat3 类型的 Uniform 值.
            * @param name Uniform 的名称.
            * @param mat Uniform 的值.
            * @return 当前 Shader 类的引用.
            */
            Shader& setMat3(const std::string& name, const glm::mat3& mat);


            /**
             * 设置 glm::mat4 类型的 Uniform 值.
             * @param value packGlm<glm::mat4> 的引用.
             * @return 当前 Shader 类的引用.
             */
            Shader& setMat4(const packGlm<glm::mat4>& value);

            /**
            * 设置 glm::mat4 类型的 Uniform 值.
            * @param name Uniform 的名称.
            * @param mat Uniform 的值.
            * @return 当前 Shader 类的引用.
            */
            Shader& setMat4(const std::string& name, const glm::mat4& mat);

        private:
            GLuint ID;
    };


    /**
     * 方向枚举
     * FORWARD - 前
     * BACKWARD - 后
     * LEFT - 左
     * RIGHT - 右
     */
    enum Direction {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    class Camera {
        public:
            explicit Camera(
                glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3 up       = glm::vec3(0.0f, 1.0f, 0.0f),
                GLfloat yaw        = -90.0f,
                GLfloat pitch      = 0.0f
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

    #define MAX_BONE_INFLUENCE 4

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        glm::vec3 Tangent;
        glm::vec3 Bitangent;
        int m_BoneIDs[MAX_BONE_INFLUENCE];
        float m_Weights[MAX_BONE_INFLUENCE];
    };

    struct Texture {
        GLuint id;
        std::string type;
        std::string path;
    };

    class Mesh {
        public:
            std::vector<Vertex> vertices;
            std::vector<GLuint> indices;
            std::vector<Texture> textures;
            Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices,
                 const std::vector<Texture>& textures);
            void Draw(Shader& shader) const;

        private:
            GLuint VAO{}, VBO{}, EBO{};
            GLvoid setupMesh();
    };

    class Model {
        public:
            explicit Model(const char* path, GLboolean gamma = GL_FALSE);
            GLvoid Draw(Shader& shader) const;

        private:
            std::vector<Texture> textures_loaded;
            std::vector<Mesh> meshes;
            std::string directory;
            GLboolean gammaCorrection;
            GLvoid loadModel(const std::string& path);
            GLvoid processNode(const aiNode* node, const aiScene* scene);
            Mesh processMesh(aiMesh* mesh, const aiScene* scene);
            std::vector<Texture> loadMaterialTextures(const aiMaterial* mat, aiTextureType type,
                                                      const std::string& typeName);
    };

    class Init {
        public:

            /**
             * 设置窗口宽度.
             * @param argScreenWidth 窗口宽度.
             * @return 当前 Init 类的实例引用.
             */
            Init& setScreenWidth(GLuint argScreenWidth);

            /**
             * 获取窗口宽度.
             * @return 窗口宽度.
             */
            [[nodiscard]] GLuint getScreenWidth() const;

            /**
             * 设置窗口高度.
             * @param argScreenHeight 窗口高度.
             * @return 当前 Init 类的实例引用.
             */
            Init& setScreenHeight(GLuint argScreenHeight);

            /**
             * 获取窗口高度.
             * @return 窗口高度.
             */
            [[nodiscard]] GLuint getScreenHeight() const;

            /**
             * 获取单实例类的实例引用.
             * @return 当前 Init 类的实例引用.
             */
            static Init& getInstance();

            /**
             * 设置摄像机.
             * @param argCamera Camera类的引用.
             * @return 当前 Init 类的实例引用.
             */
            Init& setCamera(const Camera& argCamera);

            /**
             * 获取摄像机.
             * @return 当前 Init 类的实例上的 Camera.
             */
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


    /**
     * 帧大小改变事件.
     * @param window 当前窗口句柄.
     * @param width 改变后的窗口宽度.
     * @param height 改变后的窗口高度.
     */
    GLvoid framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height);

    /**
     * 鼠标移动事件.
     * @param window 当前窗口句柄.
     * @param xPos 鼠标指针的 x 轴位置.
     * @param yPos 鼠标指针的 y 轴位置.
     */
    GLvoid mouse_callback(GLFWwindow* window, GLdouble xPos, GLdouble yPos);


    /**
     * 鼠标滚轮事件.
     * @param window 当前窗口句柄.
     * @param xOffset 鼠标滚轮的 x 轴偏移值.
     * @param yOffset 鼠标滚轮的 y 轴偏移值.
     */
    GLvoid scroll_callback(GLFWwindow* window, GLdouble xOffset, GLdouble yOffset);


    /**
     * 键盘输入事件.
     * @param window 当前窗口句柄.
     */
    GLvoid processInput(GLFWwindow* window);


    /**
     * 纹理加载函数.
     * @param path 纹理文件路径
     * @return 纹理 ID.
     */
    GLuint loadTexture(GLchar const* path);
}

#endif //OPENGL_TOOLS_H
