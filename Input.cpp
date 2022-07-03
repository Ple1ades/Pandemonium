#include "Utilities.h"

void getInput(bool * running){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type)
        {
        default:
            break;
        case SDL_QUIT:
            *running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym){
                default:
                    break;
                case SDLK_ESCAPE:
                    *running = false;
                    break;
            }
            break;
        }
           
    }
    
}