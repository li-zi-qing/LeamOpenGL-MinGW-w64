#include <OpenGLTools.h>
#include <stb_image.h>
#include <iostream>
using namespace OpenGLTools;

GLvoid OpenGLTools::framebuffer_size_callback(GLFWwindow* window, const GLint width, const GLint height)
{
    glViewport(0, 0, width, height);
}

GLvoid OpenGLTools::processInput(GLFWwindow* window)
{
    Camera camera = Init::getInstance().getCamera();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.processKeyboard(FORWARD, Init::getInstance().getDeltaTime());
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.processKeyboard(BACKWARD, Init::getInstance().getDeltaTime());
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.processKeyboard(LEFT, Init::getInstance().getDeltaTime());
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.processKeyboard(RIGHT, Init::getInstance().getDeltaTime());
    }
    Init::getInstance().setCamera(camera);
}

GLvoid OpenGLTools::mouse_callback(GLFWwindow* window, const GLdouble xPos, const GLdouble yPos)
{
    Init& initInstance = Init::getInstance();
    if (initInstance.getFirstMouse())
    {
        initInstance.setLastX(static_cast<GLfloat>(xPos));
        initInstance.setLastY(static_cast<GLfloat>(yPos));
        initInstance.setFirstMouse(GL_FALSE);
    }

    const GLfloat xOffset = static_cast<GLfloat>(xPos) - initInstance.getLastX();
    const GLfloat yOffset = initInstance.getLastY() - static_cast<GLfloat>(yPos);

    initInstance.setLastX(static_cast<GLfloat>(xPos));
    initInstance.setLastY(static_cast<GLfloat>(yPos));

    Camera camera = initInstance.getCamera();
    camera.processMouseMovement(xOffset, yOffset);
    initInstance.setCamera(camera);
}

GLvoid OpenGLTools::scroll_callback(GLFWwindow* window, GLdouble xOffset, const GLdouble yOffset)
{
    Init& initInstance = Init::getInstance();
    Camera camera = initInstance.getCamera();
    camera.processMouseScroll(static_cast<GLfloat>(yOffset));
    initInstance.setCamera(camera);
}

GLuint OpenGLTools::loadTexture(GLchar const* path)
{
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    if (unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0))
    {
        GLenum format = 0;
        if (nrComponents == 1)
        {
            format = GL_RED;
        }
        else if (nrComponents == 3)
        {
            format = GL_RGB;
        }
        else if (nrComponents == 4)
        {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format), width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "纹理无法在路径上加载: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
