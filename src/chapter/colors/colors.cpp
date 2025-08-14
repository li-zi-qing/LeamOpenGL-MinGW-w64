#include <OpenGLTools.h>
#include <chapter/colors/Uniform.h>
using namespace OpenGLTools;

GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
};

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main() {
    Init &initInstance = Init::getInstance();
    initInstance
            .setTitle("Colors | 颜色")
            .setCamera(Camera(glm::vec3(0.0f, 0.0f, 3.0f)))
            .setScreenHeight(600)
            .setScreenWidth(800)
            .builder();
    GLFWwindow *window = initInstance.getWindow();

    Shader lightingShader(
        "resources/shader/colors/colors.vert",
        "resources/shader/colors/colors.frag"
    );
    Shader lightCubeShader(
        "resources/shader/colors/light_cube.vert",
        "resources/shader/colors/light_cube.frag"
    );

    GLuint VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);
    GLuint lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        const auto currentFrame = static_cast<float>(glfwGetTime());
        initInstance.setDeltaTime(currentFrame - initInstance.getLastFrame());
        initInstance.setLastFrame(currentFrame);
        processInput(window);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        lightingShader.use();
        lightingShader.setVec3(uniform.objectColor(glm::vec3(1.0f, 0.5f, 0.31f)));
        lightingShader.setVec3(uniform.lightColor(glm::vec3(1.0f, 1.0f, 1.0f)));
        glm::mat4 projection = glm::perspective(
            glm::radians(initInstance.getCamera().getZoom()),
            static_cast<float>(initInstance.getScreenWidth()) / static_cast<float>(initInstance.getScreenHeight()),
            0.1f,
            100.0f
        );
        glm::mat4 view = initInstance.getCamera().getViewMatrix();
        lightingShader.setMat4(uniform.projection(projection));
        lightingShader.setMat4(uniform.view(view));
        auto model = glm::mat4(1.0f);
        lightingShader.setMat4(uniform.model(model));
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        lightCubeShader.use();
        lightCubeShader.setMat4(uniform.projection);
        lightCubeShader.setMat4(uniform.view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightCubeShader.setMat4(uniform.model(model));
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
