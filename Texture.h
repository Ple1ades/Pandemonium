#ifndef TEXTURE_H
#define TEXTURE_H
#include "Utilities.h"
class Texture {
public:
    int val;
    unsigned int texture, width, height, nrChannels;
    float v1,v2,u1,u2;
    operator int() const {return val;}
    Texture (int n) : val (n){

    }
    Texture(){}
    Texture(GLint xWrap, GLint yWrap, GLint minFilter, GLint maxFilter, const char * path, GLenum imageFormat, float _u1, float _v1, float _u2, float _v2){
        this->initTexture(xWrap, yWrap, minFilter, maxFilter, path, imageFormat, _u1, _u2, _v1, _v2);
    }
    void initTexture(GLint xWrap, GLint yWrap, GLint minFilter, GLint maxFilter, const char * path, GLenum imageFormat, float _u1, float _v1, float _u2, float _v2){
        unsigned int _texture;
        glGenTextures(1, &_texture);
        std::cout<<_texture;

        glBindTexture(GL_TEXTURE_2D, _texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, xWrap);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, yWrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);

        int _width, _height, _nrChannels;
        unsigned char *data = stbi_load(path, &_width, &_height, &_nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, _width, _height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        this->texture = _texture;
        this->width = _width;
        this->height = _height;
        this->nrChannels = _nrChannels;
        this->v1=_v1;
        this->v2=_v2;
        this->u1=_u1;
        this->u2=_u2;
    }
};

#endif