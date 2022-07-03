#pragma once
#include <cstdint>
#include <string>
#include <iostream>
#include <cmath>
// https://github.com/Auburn/FastNoiseLite/blob/master/Cpp/README.md
#include "FastNoiseLite/FastNoiseLite.h"
#include <box2d/box2d.h>
#include <string>
#include <SDL2/SDL.h>
#include <gl\glew.h>
#include <SDL2/SDL_opengl.h>
#include <gl\GLU.h>

#include <map>
#include <vector>
#include <variant>

#define CLAMP(x, upper, lower) (std::max(upper, std::min(x, lower)))

constexpr static const int32_t g_kWindowWidth             = 1920;
constexpr static const int32_t g_kWindowHeight            = 1080;
constexpr static const int32_t g_kRenderWidth             = g_kWindowWidth / 2;
constexpr static const int32_t g_kRenderHeight            = g_kWindowHeight / 2;
constexpr static const int32_t g_kRenderDeviceFlags       = -1;
constexpr static const int32_t g_kErrorOccurred           = -1;
constexpr static const int32_t g_kVelocityIterations      = 6;
constexpr static const int32_t g_kPositionIterations      = 2;

constexpr static const char* g_kWindowTitle =             "PixelPusher";



int32_t e(int32_t result, std::string errorMessage)
{
	if (result)
		std::cout << errorMessage;

	return result;
}


//Marsaglia's xorshf generator (Fast Random Function)
static uint32_t s_randX = 123456789;
static uint32_t s_randY = 362436069;
static uint32_t s_randZ = 521288629;

inline uint32_t FastRand(void) 
{   
    uint32_t t;

    s_randX ^= s_randX << 16;
    s_randX ^= s_randX >> 5;
    s_randX ^= s_randX << 1;

    t = s_randX;
    s_randX = s_randY;
    s_randY = s_randZ;
    s_randZ = t ^ s_randX ^ s_randY;

    return s_randZ;
}

class Vector3{
    public:
    int x;
    int y;
    int z;

    Vector3(){

    }
    Vector3(int _x, int _y){
        x = _x;
        y = _y;
    }
    Vector3(int _x, int _y, int _z){
        x = _x;
        y = _y;
        z = _z;
    }
};