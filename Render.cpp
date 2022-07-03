#include "Utilities.h"

namespace Render{
    int initialize(SDL_Window * window, SDL_GLContext * context){
        if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0){
            return 1;
        }
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        
        window = SDL_CreateWindow(
            "Renderer test", 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            g_kWindowWidth,
            g_kWindowHeight,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (window == NULL){
            SDL_Quit();
            return 1;
        }
        *context = SDL_GL_CreateContext(window);
        if (context == NULL){
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }

        if (glewInit() != GLEW_OK){
            SDL_GL_DeleteContext(context);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }
        return 0;
    }
};