#include <OpenGLTools.h>
#include <chapter/model/Uniform.h>
#include <filesystem>
namespace fs = std::filesystem;
using namespace OpenGLTools;

int main() {
    Init& initInstance = Init::getInstance();
    initInstance
            .setScreenHeight(600)
            .setScreenWidth(800)
            .setTitle("Model | 模型")
            .setCamera(Camera(glm::vec3(0.0f, 0.0f, 3.0f)))
            .builder();
    GLFWwindow* window = initInstance.getWindow();

    constexpr float vertices[] = {
        // positions         // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f / 3.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f / 3.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f / 3.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 1.0f / 3.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 2.0f / 3.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 2.0f / 3.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 2.0f / 3.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 1.0f / 3.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 1.0f / 3.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 2.0f / 3.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, -1.0f,
        -0.5f, -0.5f, 0.5f, 2.0f / 3.0f, -1.0f,
        -0.5f, 0.5f, 0.5f, 2.0f / 3.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 2.0f / 3.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, -1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, -1.0f,
        0.5f, -0.5f, 0.5f, 2.0f / 3.0f, -1.0f,
        0.5f, 0.5f, 0.5f, 2.0f / 3.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 1.0f / 3.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 2.0f / 3.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 2.0f / 3.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 2.0f / 3.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 1.0f / 3.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f / 3.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f / 3.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f / 3.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f / 3.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader shader("resources/shader/model/model.vert", "resources/shader/model/model.frag");
    Shader lightCubeShader("resources/shader/model/light_cube.vert", "resources/shader/model/light_cube.frag");
    const Model loadingModel("resources/object/backpack/backpack.obj");
    const GLuint texture = loadTexture(fs::path("resources/images/cubeTexture.png").string().c_str());

    shader
            .use()
            .setVec3(uniform.light.ambient(glm::vec3(0.9176f, 0.5373f, 0.3451f)))
            .setVec3(uniform.light.diffuse(glm::vec3(0.01f, 0.01f, 0.01f)))
            .setVec3(uniform.light.specular(glm::vec3(1.0f)))
            .setFloat(uniform.shininess(16.0f));

    lightCubeShader
            .use()
            .setInt(uniform.Texture(0))
            .setVec4(uniform.lightColor(glm::vec4(0.9176f, 0.5373f, 0.3451f, 0.5f)));

    glfwSetTime(0);
    GLfloat currentAngle = 0.0f;
    auto lightPos = glm::vec3(0.0f, 0.0f, -10.0f);
    while (!glfwWindowShouldClose(window)) {
        glDisable(GL_BLEND);
        GLdouble r              = 5.0f;
        Camera camera           = initInstance.getCamera();
        const auto currentFrame = static_cast<GLfloat>(glfwGetTime());
        initInstance.setDeltaTime(currentFrame - initInstance.getLastFrame());
        initInstance.setLastFrame(currentFrame);
        processInput(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto projection = glm::perspective(glm::radians(camera.getZoom()),
                                           static_cast<GLfloat>(initInstance.getScreenWidth()) / static_cast<GLfloat>(
                                               initInstance.getScreenHeight()), 0.1f, 100.0f);
        auto view  = camera.getViewMatrix();
        auto model = glm::mat4(1.0f);
        model      = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
        model      = glm::scale(model, glm::vec3(1.0f));
        lightPos.x = static_cast<GLfloat>(r * sin(currentAngle));
        lightPos.y = 0;
        lightPos.z = static_cast<GLfloat>(r * (cos(currentAngle) - 1));

        shader
                .use()
                .setMat4(uniform.projection(projection))
                .setMat4(uniform.view(view))
                .setMat4(uniform.model(model))
                .setVec3(uniform.light.position(lightPos))
                .setVec3(uniform.viewPos(camera.getFront()));

        loadingModel.Draw(shader);

        model      = glm::mat4(1.0f);
        model      = translate(model, lightPos);
        model      = glm::rotate(model, currentAngle, lightPos);
        model      = scale(model, glm::vec3(1.0f));
        lightCubeShader
                .use()
                .setMat4(uniform.projection)
                .setMat4(uniform.view)
                .setMat4(uniform.model(model));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        currentAngle += 1.0f * initInstance.getDeltaTime();
        if (currentAngle >= 360.0f) {
            currentAngle = 0.0f;
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}
