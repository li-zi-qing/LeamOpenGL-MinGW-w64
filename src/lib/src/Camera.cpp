#include <iostream>
#include <OpenGLTools.h>
using namespace OpenGLTools;

Camera::Camera(
    const glm::vec3 position,
    const glm::vec3 up,
    const GLfloat yaw,
    const GLfloat pitch
)
{
    this->position = position;
    this->up = up;
    this->yaw = yaw;
    this->pitch = pitch;
    this->updateCameraVectors();
}

Camera::Camera(
    const GLfloat posX,
    const GLfloat posY,
    const GLfloat posZ,
    const GLfloat upX,
    const GLfloat upY,
    const GLfloat upZ,
    const GLfloat yaw,
    const GLfloat pitch
)
{
    this->position = glm::vec3(posX, posY, posZ);
    this->up = glm::vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    this->updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

GLvoid Camera::processKeyboard(const Direction direction, const GLfloat deltaTime)
{
    const GLfloat velocity = speed * deltaTime;
    if (direction == FORWARD)
    {
        this->position += this->front * velocity;
    }
    else if (direction == BACKWARD)
    {
        this->position -= this->front * velocity;
    }
    else if (direction == LEFT)
    {
        this->position -= this->right * velocity;
    }
    else if (direction == RIGHT)
    {
        this->position += this->right * velocity;
    }
}

GLvoid Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, const GLboolean constrainPitch)
{
    xOffset *= this->sensitivity;
    yOffset *= this->sensitivity;
    this->yaw += xOffset;
    this->pitch += yOffset;
    if (constrainPitch)
    {
        if (this->pitch > 89.0)
        {
            this->pitch = 89.0;
        }
        else if (this->pitch < -89.0)
        {
            this->pitch = -89.0;
        }
    }
    this->updateCameraVectors();
}

GLvoid Camera::processMouseScroll(const GLfloat yOffset)
{
    this->zoom -= yOffset;
    if (this->zoom < 1.0f)
    {
        this->zoom = 1.0f;
    }
    else if (this->zoom > 45.0f)
    {
        this->zoom = 45.0f;
    }
}

GLfloat Camera::getYaw() const
{
    return yaw;
}

GLfloat Camera::getPitch() const
{
    return pitch;
}

GLfloat Camera::getSensitivity() const
{
    return sensitivity;
}

GLfloat Camera::getZoom() const
{
    return zoom;
}

glm::vec3 Camera::getPosition() const
{
    return position;
}

glm::vec3 Camera::getFront() const
{
    return front;
}

glm::vec3 Camera::getUp() const
{
    return up;
}

glm::vec3 Camera::getRight() const
{
    return right;
}

GLvoid Camera::updateCameraVectors()
{
    glm::vec3 frontTemp;
    frontTemp.x = static_cast<GLfloat>(cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)));
    frontTemp.y = static_cast<GLfloat>(sin(glm::radians(this->pitch)));
    frontTemp.z = static_cast<GLfloat>(sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)));
    this->front = glm::normalize(frontTemp);
    right = glm::normalize(glm::cross(this->front, up));
    up = glm::normalize(glm::cross(right, this->front));
}
