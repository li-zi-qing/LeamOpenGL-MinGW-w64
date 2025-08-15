CMAKE_MINIMUM_REQUIRED(VERSION 4.0)
PROJECT(OpenGL)

# 节章名
SET(CHAPTER "materials")
SET(MAIN_SRC_PATH ${PROJECT_SOURCE_DIR}/src/chapter)

# 自定义库文件
SET(CUSTOM_INCLUDE ${PROJECT_SOURCE_DIR}/src/lib/include)
SET(CUSTOM_SRC ${PROJECT_SOURCE_DIR}/src/lib/src)

# Shader 文件路径
SET(SHADER_PATH ${PROJECT_SOURCE_DIR}/resources/shader/${CHAPTER})

# Uniform.h 头文件输出路径
SET(OUTPUT_PATH ${PROJECT_SOURCE_DIR}/src/lib/include/chapter/${CHAPTER})

# 工具配置文件.
SET(CONFIG_PATH ${PROJECT_SOURCE_DIR}/resources/shader/Shader.config.json)

# 收集所有的自定义库 .cpp 文件到 ALL_CUSTOM_SRC.
AUX_SOURCE_DIRECTORY(
        ${CUSTOM_SRC}
        ALL_CUSTOM_SRC
)

# 全局库文件.
SET(
        LIB_PATH_LIST
        ${PROJECT_SOURCE_DIR}/libGlobal/glfw # GLFW
        ${PROJECT_SOURCE_DIR}/libGlobal/glad # GLAD2
        ${PROJECT_SOURCE_DIR}/libGlobal/glm # GLM
)
SET(
        LIB_STB
        ${PROJECT_SOURCE_DIR}/libGlobal/stb
)

# 向 CMAKE_PREFIX_PATH 添加全局库路径.
SET(
        CMAKE_PREFIX_PATH
        ${LIB_PATH_LIST}
        ${CMAKE_PREFIX_PATH}
)

# 获取 LIB_PATH 中 GLAD 的路径.
LIST(GET LIB_PATH_LIST 1 GLAD_PATH)

# 导入 GLFW 库.
find_package(
        glfw3
        REQUIRED
        CONFIG
)

# 导入 GLM 库.
find_package(
        glm
        REQUIRED
        CONFIG
)

# 添加子项目 ScanVariables.
ADD_SUBDIRECTORY(
        ${PROJECT_SOURCE_DIR}/scanVariables
)

# 添加编译目标 OpenGL.
ADD_EXECUTABLE(
        ${PROJECT_NAME}
        ${MAIN_SRC_PATH}/${CHAPTER}/${CHAPTER}.cpp
        ${GLAD_PATH}/src/gl.c
        ${LIB_STB}/src/stb_image.cpp
        ${ALL_CUSTOM_SRC}
)

# 自定义目标用于扫描 Uniform 变量
ADD_CUSTOM_TARGET(
        ScanUniform
        COMMAND $<TARGET_FILE:ScanVariables> ${SHADER_PATH} ${CONFIG_PATH} ${OUTPUT_PATH} Uniform
        DEPENDS ScanVariables
        COMMENT "扫描 Uniform 变量..."
)

target_compile_features(
        ${PROJECT_NAME}
        PRIVATE
        cxx_std_23
)

# 链接 GLFW 库.
TARGET_LINK_LIBRARIES(
        ${PROJECT_NAME}
        PRIVATE
        glfw
        glm::glm
)

# 设置项目的 include.
TARGET_INCLUDE_DIRECTORIES(
        ${PROJECT_NAME}
        PRIVATE
        ${GLAD_PATH}/include
        ${LIB_STB}/include
        ${CUSTOM_INCLUDE}
)

# 自定义目标拷贝资源文件到构建目录.
ADD_CUSTOM_TARGET(
        CopyResources
        ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
        COMMENT "复制文件到构建目录..."
)