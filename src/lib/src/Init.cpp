#include <OpenGLTools.h>
#include <iostream>
#if __WIN32__
#include <windows.h>
#endif
#include <iomanip>
using namespace OpenGLTools;

Init::Init(
    const GLuint screenWidth,
    const GLuint screenHeight,
    Camera camera,
    const GLfloat lastX,
    const GLfloat lastY,
    const GLboolean firstMouse,
    const GLfloat deltaTime,
    const GLfloat lastFrame,
    const GLchar* title
) :
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    camera(camera),
    lastX(lastX),
    lastY(lastY),
    firstMouse(firstMouse),
    deltaTime(deltaTime),
    lastFrame(lastFrame),
    title(title)
{
    this->lastX = static_cast<GLfloat>(screenWidth) / 2.0f;
    this->lastY = static_cast<GLfloat>(screenHeight) / 2.0f;
}

Init& Init::setScreenWidth(const GLuint argScreenWidth)
{
    this->screenWidth = argScreenWidth;
    return *this;
}

Init::~Init()
{
    if (this->window != nullptr)
    {
        glfwDestroyWindow(this->window);
        std::cout << "卸载 Window 指针..." << std::endl;
    }
    glfwTerminate();
    std::cout << "卸载 GLFW...\n";
}

GLuint Init::getScreenWidth() const
{
    return this->screenWidth;
}

GLuint Init::getScreenHeight() const
{
    return this->screenHeight;
}

Camera Init::getCamera() const
{
    return this->camera;
}

GLfloat Init::getLastX() const
{
    return this->lastX;
}

GLfloat Init::getLastY() const
{
    return this->lastY;
}

GLboolean Init::getFirstMouse() const
{
    return this->firstMouse;
}

GLfloat Init::getDeltaTime() const
{
    return this->deltaTime;
}

GLfloat Init::getLastFrame() const
{
    return this->lastFrame;
}

GLFWwindow* Init::getWindow() const
{
    return this->window;
}

Init& Init::setTitle(const GLchar* argTitle)
{
    this->title = argTitle;
    return *this;
}

GLboolean Init::builder()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* tempWindow = glfwCreateWindow(
        static_cast<int>(this->screenWidth),
        static_cast<int>(this->screenHeight),
        this->title,
        nullptr,
        nullptr
    );
    if (tempWindow == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return GL_FALSE;
    }
    glfwMakeContextCurrent(tempWindow);
    glfwSetFramebufferSizeCallback(tempWindow, framebuffer_size_callback);
    glfwSetCursorPosCallback(tempWindow, mouse_callback);
    glfwSetScrollCallback(tempWindow, scroll_callback);
    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return GL_FALSE;
    }
    glEnable(GL_DEPTH_TEST);
    this->window = tempWindow;
    return GL_TRUE;
}

Init& Init::setScreenHeight(const GLuint argScreenHeight)
{
    this->screenHeight = argScreenHeight;
    return *this;
}

Init& Init::getInstance()
{
    static Init initInstance;
    return initInstance;
}

Init& Init::setCamera(const Camera& argCamera)
{
    this->camera = argCamera;
    return *this;
}

Init& Init::setLastX(const GLfloat argLastX)
{
    this->lastX = argLastX;
    return *this;
}

Init& Init::setLastY(const GLfloat argLastY)
{
    this->lastY = argLastY;
    return *this;
}

Init& Init::setFirstMouse(const GLboolean argFirstMouse)
{
    this->firstMouse = argFirstMouse;
    return *this;
}

Init& Init::setDeltaTime(const GLfloat argDeltaTime)
{
    this->deltaTime = argDeltaTime;
    return *this;
}

Init& Init::setLastFrame(const GLfloat argLastFrame)
{
    this->lastFrame = argLastFrame;
    return *this;
}
