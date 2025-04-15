cmake_minimum_required(VERSION 3.16)
project(LearnOpenGLApp)

set(CMAKE_CXX_STANDARD 17)

# GLFW
add_subdirectory(libs/glfw)
include_directories(libs/glfw/include)

# GLAD
include_directories(libs/glad/include)
file(GLOB GLAD_SRC libs/glad/src/*.c)

# GLM
include_directories(libs/glm)

# Source files
file(GLOB SRC_FILES src/*.cpp)

# Create executable
add_executable(LearnOpenGLApp ${SRC_FILES} ${GLAD_SRC})
target_link_libraries(LearnOpenGLApp glfw ${CMAKE_DL_LIBS})
