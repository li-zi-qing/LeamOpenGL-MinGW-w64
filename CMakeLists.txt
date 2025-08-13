CMAKE_MINIMUM_REQUIRED(VERSION 3.31)
PROJECT(OpenGL)
SET(CMAKE_CXX_STANDARD 26)

# 节章名
SET(CHAPTER "shaders")
SET(MAIN_SRC_PATH ${PROJECT_SOURCE_DIR}/src/chapter)

# 自定义库文件
SET(CUSTOM_INCLUDE ${PROJECT_SOURCE_DIR}/src/lib/include)
SET(CUSTOM_SRC ${PROJECT_SOURCE_DIR}/src/lib/src)

#收集所有的自定义库 .cpp 文件到 ALL_CUSTOM_SRC
AUX_SOURCE_DIRECTORY(
        ${CUSTOM_SRC}
        ALL_CUSTOM_SRC
)

# 全局库文件
SET(
        LIB_PATH_LIST
        ${PROJECT_SOURCE_DIR}/libGlobal/glfw # GLFW
        ${PROJECT_SOURCE_DIR}/libGlobal/glad # GLAD2
        ${PROJECT_SOURCE_DIR}/libGlobal/glm # GLM
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

# 添加编译目标 OpenGL
ADD_EXECUTABLE(
        ${PROJECT_NAME}
        ${MAIN_SRC_PATH}/${CHAPTER}/${CHAPTER}.cpp
        ${GLAD_PATH}/src/gl.c
        ${ALL_CUSTOM_SRC}
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
        ${CUSTOM_INCLUDE}
)

# 自定义目标拷贝资源文件到构建目录.
ADD_CUSTOM_TARGET(
        CopyResources
        ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
        COMMENT "复制文件到构建目录..."
)