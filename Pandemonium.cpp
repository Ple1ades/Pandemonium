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
    void ProcessInput(GLFWwindow * window, glm::vec3 *cameraPos, glm::vec3 *cameraFront, glm::vec3 *cameraUp, float *deltaTime){
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);
        }
        const float cameraSpeed = 2.5f * (*deltaTime); // adjust accordingly
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            *cameraPos += cameraSpeed * (*cameraFront);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            *cameraPos -= cameraSpeed * (*cameraFront);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            *cameraPos -= glm::normalize(glm::cross(*cameraFront, *cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            *cameraPos += glm::normalize(glm::cross(*cameraFront, *cameraUp)) * cameraSpeed;
    }
    void Render(){

    }
};