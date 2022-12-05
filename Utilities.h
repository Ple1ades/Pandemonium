#pragma once
#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdint>
#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>
// https://github.com/Auburn/FastNoiseLite/blob/master/Cpp/README.md
#include "Includes/FastNoiseLite/FastNoiseLite.h"
#include <box2d/box2d.h>
#include <string>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include "Includes/std_image.h"

#include <map>
#include <vector>
#include <variant>

#include "Constants.h"

#define CLAMP(x, upper, lower) (std::max(upper, std::min(x, lower)))



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void key_callback(GLFWwindow * window, int key, int32 scancode, int32 action, int32 mode){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
static void glfwError(int id, const char* description)
{
    std::cout << description << std::endl;
}


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
#endif