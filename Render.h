#ifndef RENDER_H
#define RENDER_H
#include "Utilities.h"


class Renderer{
public:

    Renderer(){
        
    }
    ~Renderer(){

    }
    GLFWwindow * initGLFW(){
        glfwSetErrorCallback(&glfwError);
        if (!glfwInit()) {
            exit(EXIT_FAILURE);
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

        GLFWwindow * window = glfwCreateWindow(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, Constants::WINDOW_NAME, glfwGetPrimaryMonitor(), 0);
        if (window == NULL){
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return NULL;
        }

        GLFWmonitor* monitor = glfwGetWindowMonitor(window);
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, key_callback);

        glewExperimental = GL_TRUE;
        glewInit();

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_SCISSOR_TEST);
        
        int32 width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0,0, width, height);
    
        
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        return window;
    }
    void DrawSprite(){

    }
    void Render(){
        
    }
};
#endif