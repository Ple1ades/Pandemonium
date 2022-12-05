#include "Utilities.h"


class Pandemonium{
public:
    bool running = true;
    Pandemonium(){

    }
    ~Pandemonium(){

    }
    void Init(){

    }
    void Update(float dt){

    }
    void ProcessInput(GLFWwindow * window, float *deltaTime){
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);
        }
    }
    void Render(){

    }
};