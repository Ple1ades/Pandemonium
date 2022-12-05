#ifndef OBJECTS_H
#define OBJECTS_H
#include "Utilities.h"
#include "Texture.h"
class Object {
public:
    int16 x, y, width, height;
    Texture texture;
    
    Object(int16 _x = (int16)NULL, int16 _y = (int16)NULL, Texture _texture = NULL){
        x = _x;

        y = _y;
        texture = _texture;
    }
    void updateUVs(float * uvs, Object * objects, int i){
        // Top right
        uvs[i * 12] = (objects)[i].texture.u2;
        uvs[i * 12 + 1] = (objects)[i].texture.v2;
        // Bottom right
        uvs[i * 12 + 2] = (objects)[i].texture.u1;
        uvs[i * 12 + 3] = (objects)[i].texture.v1;
        // Top  left
        uvs[i * 12 + 4] = (objects)[i].texture.u2;
        uvs[i * 12 + 5] = (objects)[i].texture.v1;
        // Bottom right
        uvs[i * 12 + 6] = (objects)[i].texture.u2;
        uvs[i * 12 + 7] = (objects)[i].texture.v2;
        
        //Bottom left
        uvs[i * 12 + 8] = (objects)[i].texture.u1;
        uvs[i * 12 + 9] = (objects)[i].texture.v2;
        
        //Top left
        uvs[i * 12 + 10] = (objects)[i].texture.u1;
        uvs[i * 12 + 11] = (objects)[i].texture.v1;
    }
    
};
#endif