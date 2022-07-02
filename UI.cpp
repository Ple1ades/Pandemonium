#include "Utilities.h"

class UI{
public:
    void addSprite(const char * spriteName, const char * file, SDL_Window * window, SDL_Renderer * renderer){
        SDL_Surface  * temp =  SDL_LoadBMP(file);
        SDL_SetColorKey(temp, true, ARGB(255, 0, 255, 255));
        sprites[spriteName] = SDL_CreateTextureFromSurface(renderer, SDL_ConvertSurfaceFormat(temp, SDL_GetWindowPixelFormat(window), 0));
        spriteSizes[spriteName] = getSpriteSize(sprites[spriteName]);
        SDL_FreeSurface(temp);
    }
    void drawSprite(const char * spriteName, int x, int y, SDL_Renderer * renderer){
        SDL_Rect position;
        position.x = x;
        position.y = y;
        position.w = spriteSizes[spriteName].x;
        position.h = spriteSizes[spriteName].y;

        SDL_RenderCopy(renderer, sprites[spriteName], NULL, &position);
    }
    SDL_Point getSpriteSize(SDL_Texture *texture){
        SDL_Point size;
        SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
        return size;
    }
private:
    std::map<const char *, SDL_Texture *> sprites;
    std::map<const char *, SDL_Point> spriteSizes;
};