cmake_minimum_required(VERSION 3.8)
project(engine)

# Find OpenGL package
find_package(OpenGL REQUIRED)

set(SRC_DIRECTORY src)
set(GRAPHICS_DIRECTORY ${SRC_DIRECTORY}/Graphics)
set(CORE_DIRECTORY ${SRC_DIRECTORY}/Core)
set(CONFIG_DIRECTORY ${CORE_DIRECTORY}/Config)

set(LIBS_DIRECTORY libs)
set(GLAD_DIRECTORY ${LIBS_DIRECTORY}/glad_opengl)
set(GLFW_DIRECTORY ${LIBS_DIRECTORY}/glfw)
set(GLM_DIRECTORY ${LIBS_DIRECTORY}/glm)
set(FREETYPE_DIRECTORY ${LIBS_DIRECTORY}/freetype)

set(ENGINE_INCLUDE_DIRS
    ${SRC_DIRECTORY}
    ${CONFIG_DIRECTORY}
    ${GRAPHICS_DIRECTORY}
    ${GRAPHICS_DIRECTORY}/2D
    ${SRC_DIRECTORY}/platform
)

set(LIBS_INCLUDE_DIRS
    ${GLAD_DIRECTORY}/include
    ${GLFW_DIRECTORY}/include
    ${LIBS_DIRECTORY}/stb
    ${FREETYPE_DIRECTORY}/include
)

set(CORE_SRC_FILES
    ${CORE_DIRECTORY}/Window.cpp
    ${CORE_DIRECTORY}/Input.cpp
    ${CORE_DIRECTORY}/Time.cpp
    ${CORE_DIRECTORY}/ResourceLoader.cpp
    ${CORE_DIRECTORY}/gApplication.cpp
)

set(GRAPHICS_SRC_FILES
    ${GRAPHICS_DIRECTORY}/Image.cpp
    ${GRAPHICS_DIRECTORY}/Texture.cpp
    ${GRAPHICS_DIRECTORY}/Font.cpp
    ${GRAPHICS_DIRECTORY}/RendererAPI.cpp
    ${GRAPHICS_DIRECTORY}/RenderCommand.cpp
    ${GRAPHICS_DIRECTORY}/Buffer.cpp
)

set(GRAPHICS_2D_SRC_FILES
    ${GRAPHICS_DIRECTORY}/2D/Renderer2D.cpp
    ${GRAPHICS_DIRECTORY}/2D/OrthoCamera.cpp
    ${GRAPHICS_DIRECTORY}/2D/Entity/Sprite.cpp
    ${GRAPHICS_DIRECTORY}/2D/Entity/Text.cpp
    ${GRAPHICS_DIRECTORY}/2D/Batching/SpriteBatch.cpp
    ${GRAPHICS_DIRECTORY}/2D/Batching/TextBatch.cpp
)

set(PLATFORM_SRC_FILES
    ${SRC_DIRECTORY}/platform/glfw/glfwWindow.cpp
    ${SRC_DIRECTORY}/platform/opengl/glShader.cpp
    ${SRC_DIRECTORY}/platform/opengl/glTexture.cpp
    ${SRC_DIRECTORY}/platform/opengl/glBuffer.cpp
    ${SRC_DIRECTORY}/platform/opengl/glRendererAPI.cpp
)

set(SRC_FILES
    ${CORE_SRC_FILES}
    ${GRAPHICS_SRC_FILES}
    ${GRAPHICS_2D_SRC_FILES}
    ${PLATFORM_SRC_FILES}
)

add_subdirectory(${GLAD_DIRECTORY})
add_subdirectory(${GLFW_DIRECTORY})
add_subdirectory(${FREETYPE_DIRECTORY})
add_subdirectory(${GLM_DIRECTORY})

add_library(engine STATIC ${SRC_FILES})

target_include_directories(engine
    PUBLIC
        ${ENGINE_INCLUDE_DIRS}
   PRIVATE
        ${LIBS_INCLUDE_DIRS}
)
target_link_libraries(engine PRIVATE ${OPENGL_LIBRARIES} glfw glad freetype PUBLIC glm)

target_compile_definitions(engine PRIVATE ASSETS_IMAGES_DIR="${CMAKE_SOURCE_DIR}/assets/images/" ASSETS_FONTS_DIR="${CMAKE_SOURCE_DIR}/assets/fonts/" ASSETS_SHADERS_DIR="${CMAKE_SOURCE_DIR}/assets/shaders/")