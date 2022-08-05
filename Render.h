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
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        
        GLFWwindow * window = glfwCreateWindow(g_kWindowWidth, g_kWindowHeight, "2D test", NULL, NULL);
        if (window == NULL){
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return NULL;
        }
        glfwMakeContextCurrent(window);
        
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            std::cout << "Failed to initialize GLAD" << std::endl;
            return NULL;
        }
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        glViewport(0, 0, g_kWindowWidth, g_kWindowHeight);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        return window;
    }
    void DrawSprite(){

    }
    Texture generateTexture(GLint xWrap, GLint yWrap, GLint minFilter, GLint maxFilter, const char * path, GLenum imageFormat){
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, xWrap);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, yWrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);

        int width, height, nrChannels;
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        Texture tex;
        tex.texture = texture;
        tex.width = width;
        tex.height = height;
        tex.nrChannels = nrChannels;
        return tex;
    }
};
#endif