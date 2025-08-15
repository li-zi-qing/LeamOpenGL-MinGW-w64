#include <OpenGLTools.h>
#include <filesystem>
#include <chapter/multipleLights/Uniform.h>
using namespace OpenGLTools;
namespace fs = std::filesystem;

GLfloat vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

// positions all containers
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)
};

// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f, 0.2f, 2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f, 2.0f, -12.0f),
    glm::vec3(0.0f, 0.0f, -3.0f)
};

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
    Init& initInstance = Init::getInstance();
    initInstance
        .setCamera(Camera(glm::vec3(0.0f, 0.0f, 3.0f)))
        .setScreenHeight(600)
        .setScreenWidth(800)
        .setTitle("Multiple lights | 多光源")
        .builder();
    GLFWwindow* window = initInstance.getWindow();

    Shader lightingShader("resources/shader/multipleLights/multipleLights.vert",
                          "resources/shader/multipleLights/multipleLights.frag");
    Shader lightCubeShader("resources/shader/multipleLights/light_cube.vert",
                           "resources/shader/multipleLights/light_cube.frag");

    GLuint VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    GLuint lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    const GLuint diffuseMap = loadTexture(fs::path("resources/images/container2.png").string().c_str());
    const GLuint specularMap = loadTexture(
                                           fs::path("resources/images/container2_specular.png").string().
                                           c_str());
    const GLuint maps = loadTexture(fs::path("resources/images/夏休み前.jpg").string().c_str());

    lightingShader
        .use()
        .setInt(uniform.material.diffuse(0))
        .setInt(uniform.material.specular(1))
        .setInt(uniform.spotLight.diffuse(2))
        .setFloat(uniform.material.shininess(32.0f))
        .setFloat(uniform.spotLight.constant(1.0f))
        .setFloat(uniform.spotLight.linear(0.09f))
        .setFloat(uniform.spotLight.quadratic(0.032f))
        .setFloat(uniform.spotLight.cutOff(glm::cos(glm::radians(12.5f))))
        .setFloat(uniform.spotLight.outerCutOff(glm::cos(glm::radians(15.0f))))
        .setVec3(uniform.spotLight.ambient(glm::vec3(0.0f, 0.0f, 0.0f)))
        .setVec3(uniform.spotLight.specular(glm::vec3(1.0f, 1.0f, 1.0f)))
        .setVec3(uniform.dirLight.direction(glm::vec3(-0.2f, -1.0f, -0.3f)))
        .setVec3(uniform.dirLight.ambient(glm::vec3(0.05f, 0.05f, 0.05f)))
        .setVec3(uniform.dirLight.diffuse(glm::vec3(0.8f, 0.8f, 0.8f)))
        .setVec3(uniform.dirLight.specular(glm::vec3(0.5f, 0.5f, 0.5f)))
        .setVec3(uniform.dirLight.direction(glm::vec3(-0.2f, -1.0f, -0.3f)));

    for (int i = 0; i < 4; i++)
    {
        lightingShader
            .use()
            .setVec3(uniform.pointLights[i].position(pointLightPositions[i]))
            .setVec3(uniform.pointLights[i].ambient(glm::vec3(0.05f, 0.05f, 0.05f)))
            .setVec3(uniform.pointLights[i].diffuse(glm::vec3(0.05f, 0.05f, 0.05f)))
            .setVec3(uniform.pointLights[i].specular(glm::vec3(1.0f, 1.0f, 1.0f)))
            .setFloat(uniform.pointLights[i].constant(1.0f))
            .setFloat(uniform.pointLights[i].linear(0.09f))
            .setFloat(uniform.pointLights[i].quadratic(0.032f));
    }

    while (!glfwWindowShouldClose(window))
    {
        const auto currentFrame = static_cast<GLfloat>(glfwGetTime());
        initInstance.setDeltaTime(currentFrame - initInstance.getLastFrame());
        initInstance.setLastFrame(currentFrame);
        Camera camera = initInstance.getCamera();
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto projection = glm::perspective(glm::radians(camera.getZoom()),
                                           static_cast<GLfloat>(initInstance.getScreenWidth()) / static_cast<GLfloat>(
                                               initInstance.getScreenHeight()), 0.1f, 100.0f);
        auto view = camera.getViewMatrix();
        auto model = glm::mat4(1.0f);

        lightingShader
            .use()
            .setMat4(uniform.view(view))
            .setMat4(uniform.projection(projection))
            .setMat4(uniform.model(model))
            .setVec3(uniform.spotLight.position(camera.getPosition()))
            .setVec3(uniform.spotLight.direction(camera.getFront()))
            .setVec3(uniform.viewPos(camera.getPosition()));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, maps);

        glBindVertexArray(cubeVAO);

        for (unsigned int i = 0; i < 10; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            const float angle = 20.0f * static_cast<GLfloat>(i);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            lightingShader.setMat4(uniform.model(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        lightCubeShader
            .use()
            .setMat4(uniform.projection)
            .setMat4(uniform.view);

        for (auto pointLightPosition : pointLightPositions)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPosition);
            model = glm::scale(model, glm::vec3(0.2));

            lightCubeShader.setMat4(uniform.model(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);

    return 0;
}
