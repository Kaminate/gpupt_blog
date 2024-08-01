cmake_minimum_required(VERSION 3.28)
project(gpuPathTracing)

enable_language( CXX )
enable_language( CUDA )

if( MSVC )
    set( CMAKE_VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} )
endif()

set(API_GL 0)
set(API_CU 1)
set(API ${API_GL})

add_definitions(-DAPI_GL=${API_GL})
add_definitions(-DAPI_CU=${API_CU})
add_definitions(-DAPI=${API})


set(IMGUI_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/dearimgui ${CMAKE_CURRENT_SOURCE_DIR}/submodules/dearimgui/backends ${CMAKE_CURRENT_SOURCE_DIR}/submodules/ImGuizmo/)
set(IMGUI_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/submodules/dearimgui/imgui_demo.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/submodules/dearimgui/backends/imgui_impl_glfw.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/submodules/dearimgui/imgui.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/submodules/dearimgui/imgui_draw.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/submodules/dearimgui/imgui_widgets.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/submodules/dearimgui/imgui_tables.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/submodules/dearimgui/backends/imgui_impl_opengl3.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/submodules/ImGuizmo/ImGuizmo.cpp
)
include_directories(${IMGUI_INC_DIR})


# GLM
set(GLM_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/glm)
include_directories(${GLM_INC_DIR})

# TinyGLTF
set(TINYGLTF_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/tinygltf)
include_directories(${TINYGLTF_INC_DIR})

# STB
set(STB_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/stb)
include_directories(${STB_INC_DIR})

# FileDialog
set(FILEDIALOG_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/fileDialog/src/include)
set(FILEDIALOG_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/submodules/fileDialog/src/nfd_common.c)
set(FILEDIALOG_SOURCE ${FILEDIALOG_SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/submodules/fileDialog/src/nfd_win.cpp)
include_directories(${FILEDIALOG_INC_DIR})


# # Glad
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/submodules/glad/cmake" glad_cmake)
glad_add_library(glad_gl_core_33 STATIC API gl:core=3.3)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/gladsources/glad_gl_core_33/include")
set(GLAD_SOURCE ${CMAKE_CURRENT_BINARY_DIR}/gladsources/glad_gl_core_33/src/gl.c)

# ASSIMP
set(ASSIMP_INSTALL_PDB OFF)
add_subdirectory(submodules/assimp)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/submodules/assimp/include")
include_directories(submodules/assimp/include)

# # OIDN
SET(OIDN_DEVICE_CPU FALSE)
add_subdirectory(submodules/oidn)

set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} -std=c++11)

include_directories("gpuRT/include")

set (sourceFiles
        src/Main.cpp
        src/Window.cpp
        src/App.cu
        src/ShaderGL.cpp
        src/TextureGL.cpp
        src/BufferCu.cu
        src/BufferGL.cpp
        src/Scene.cpp
        src/BVH.cpp
        ${IMGUI_SOURCE}
)

add_executable(PathTracer ${sourceFiles})
target_link_libraries(PathTracer glfw3 glew32 opengl32)

install(TARGETS PathTracer RUNTIME)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resources/ DESTINATION bin/resources)
