#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <OpenGLTools.h>
#include <light/Uniform.h>
using namespace OpenGLTools;

GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
};

int main()
{
    Init& initInstance = Init::getInstance();
    if (const GLboolean state = initInstance
                                .setCamera(Camera(glm::vec3(0.0f, 0.0f, 3.0f)))
                                .setScreenWidth(800)
                                .setScreenHeight(600)
                                .setTitle("OpenGL Light")
                                .builder();
        state == GL_FALSE)
    {
        return -1;
    }
    GLFWwindow* window = initInstance.getWindow();
    Shader lightingShader("resources/shader/light/base_light.vert", "resources/shader/light/base_light.frag");
    Shader lightCubeShader("resources/shader/light/light_cube.vert", "resources/shader/light/light_cube.frag");
    GLuint VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    GLuint lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);
    while (!glfwWindowShouldClose(window))
    {
        const auto currentFrame = static_cast<GLfloat>(glfwGetTime());
        initInstance.setDeltaTime(currentFrame - initInstance.getLastFrame());
        initInstance.setLastFrame(currentFrame);
        processInput(window);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto projection = glm::perspective(
            glm::radians(initInstance.getCamera().getZoom()),
            static_cast<GLfloat>(initInstance.getScreenWidth()) / static_cast<GLfloat>(initInstance.
                getScreenHeight()),
            0.1f,
            100.0f);
        lightingShader
            .use()
            .setVec3(uniform.objectColor(glm::vec3(1.0f, 0.5f, 0.31f)))
            .setVec3(uniform.lightColor(glm::vec3(1.0f, 1.0f, 1.0f)))
            .setVec3(uniform.lightPos(glm::vec3(1.2f, 1.0f, 2.0f)))
            .setVec3(uniform.viewPos(initInstance.getCamera().getPosition()))
            .setMat4(uniform.projection(projection))
            .setMat4(uniform.view(initInstance.getCamera().getViewMatrix()))
            .setMat4(uniform.model(glm::mat4(1.0f)));
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        auto model = glm::mat4(1.0f);
        model = glm::translate(model, static_cast<glm::vec3>(uniform.lightPos));
        model = glm::scale(model, glm::vec3(0.2f));
        lightCubeShader
            .use()
            .setMat4(uniform.projection)
            .setMat4(uniform.view)
            .setMat4(uniform.model(model));
        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
    return 0;
}
