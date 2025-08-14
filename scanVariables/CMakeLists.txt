CMAKE_MINIMUM_REQUIRED(VERSION 4.0)
PROJECT(ScanVariables)

SET(CUSTOM_LIB_PATH ${PROJECT_SOURCE_DIR}/src/lib)
SET(SRC_PATH ${PROJECT_SOURCE_DIR}/src)

LIST(
		APPEND
		CMAKE_PREFIX_PATH
        ${PROJECT_SOURCE_DIR}/../libGlobal/json
)

FIND_PACKAGE(
        nlohmann_json
        CONFIG
        REQUIRED
)

ADD_EXECUTABLE(
		${PROJECT_NAME}
		${SRC_PATH}/ScanVariables.cpp
		${CUSTOM_LIB_PATH}/src/ScanVariablesTools.cpp
)

target_compile_features(
        ${PROJECT_NAME}
        PRIVATE
        cxx_std_23
)

target_include_directories(
		${PROJECT_NAME}
		PRIVATE
		${CUSTOM_LIB_PATH}/include
)

target_link_libraries(
		${PROJECT_NAME}
		PRIVATE
		nlohmann_json
)

INSTALL(
		TARGETS ${PROJECT_NAME}
		DESTINATION bin
)