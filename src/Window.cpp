#include "Window.h"

#include "glad/gl.h"
//#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <iostream>

namespace gpupt
{

window::window(uint32_t Width, uint32_t Height)
{
    this->Width = Width;
    this->Height = Height;
    
    if(glfwInit() != GLFW_TRUE)
    {
        std::cout << "Error initializing GLFW" << std::endl;
        exit(0);
    }

    GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* VideoMode = glfwGetVideoMode(PrimaryMonitor);
    if(this->Width == 0 || this->Height == 0)
    {
        this->Width = VideoMode->width;
        this->Height = VideoMode->height;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    glfwWindowHint(GLFW_DECORATED, true);
    glfwWindowHint(GLFW_RESIZABLE, true);

#if API==API_GL
    this->Handle = glfwCreateWindow(this->Width, this->Height, "GPU Path Tracing - OpenGL", nullptr, nullptr);
#elif API==API_CU
    this->Handle = glfwCreateWindow(this->Width, this->Height, "GPU Path Tracing - Cuda", nullptr, nullptr);
#endif 

    if(this->Handle == nullptr)
    {
        std::cout << "Error Creating Window" << std::endl;
        exit(0);
    }

    glfwMakeContextCurrent(this->Handle);
    glfwSwapInterval(0);

    glfwSetWindowUserPointer(this->Handle, (void*)this);


    if( !gladLoadGL( ( GLADloadfunc )glfwGetProcAddress ) )
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(0);
    }
}


bool window::ShouldClose() const
{
    return glfwWindowShouldClose(this->Handle);
}

void window::PollEvents() const
{
    glfwPollEvents();
}


void window::Present()
{
    glfwSwapBuffers(this->Handle);
}

window::~window()
{
    glfwDestroyWindow(Handle);
    glfwTerminate();
}

}