
//#include "MapGen.cpp"
#include "Render.h"
#include "Pandemonium.cpp"
#include "Shader.h"
#include "Objects.h"

#include "Utilities.h"

GLFWwindow* window;



Object objects[Constants::OBJECT_COUNT];
int16 vertices[Constants::OBJECT_COUNT * 12];
float uvs[Constants::OBJECT_COUNT * 12];

void updateVertices(int i){
    // Top rights
    vertices[i * 12] = (objects)[i].x + (objects)[i].texture.width;
    vertices[i * 12 + 1] = (objects)[i].y;
    // Bottom right
    vertices[i * 12 + 2] = (objects)[i].x + (objects)[i].texture.width;
    vertices[i * 12 + 3] = (objects)[i].y + (objects)[i].texture.height;
    // Top  left
    vertices[i * 12 + 4] = (objects)[i].x;
    vertices[i * 12 + 5] = (objects)[i].y;
    // Bottom right
    vertices[i * 12 + 6] = (objects)[i].x + (objects)[i].texture.width;
    vertices[i * 12 + 7] = (objects)[i].y + (objects)[i].texture.height;
    
    //Bottom left
    vertices[i * 12 + 8] = (objects)[i].x;
    vertices[i * 12 + 9] = (objects)[i].y + (objects)[i].texture.height;
    
    //Top left
    vertices[i * 12 + 10] = (objects)[i].x;
    vertices[i * 12 + 11] = (objects)[i].y;
}
void update(){
    for (uint32 i = 0; i < Constants::OBJECT_COUNT; i++){
        objects[i].x = rand() % (Constants::WINDOW_WIDTH - 5);
        objects[i].y = rand() % (Constants::WINDOW_HEIGHT - 5);
        updateVertices(i);
        
    }


    //std::cout<<vertices[0]/1920.0f<<" "<<vertices[1]/1080.0f<<" "<<
    //    vertices[2]/1920.0f<<" "<<vertices[3]/1080.0f<<" "<<

    //    vertices[4]/1920.0f<<" "<<vertices[5]/1080.0f<<" "<<
    //    vertices[6]/1920.0f<<" "<<vertices[7]/1080.0f<<" "<<
    //    vertices[8]/1920.0f<<" "<<vertices[9]/1080.0f<<" "<<
    //    vertices[10]/1920.0f<<" "<<vertices[11]/1080.0f<<std::endl;;
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
}

void render(){
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glDrawArrays(GL_TRIANGLES, 0, Constants::OBJECT_COUNT * 6);
    glfwSwapBuffers(window);
}

int main()
{

    srand((unsigned int)time(0));
    bool running=true;
    bool firstFrame=true;
    // Graphics
    Renderer renderer;
    window = renderer.initGLFW();

    Shader shader("Shaders/vertex.glsl", "Shaders/fragment.glsl");

    Texture textures[] = { 
        Texture(GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST, "./wall.jpg", GL_RGB, 1.0, 0.0, 0.0, 1.0), 
        Texture(GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST, "./awesomeface.png", GL_RGBA, 1.0, 0.0, 0.0, 1.0)
    };



    for (uint32 i = 0; i < Constants::OBJECT_COUNT; i++){
        Texture t = textures[0];

        objects[i] = {
            (int16)(rand() % (Constants::WINDOW_WIDTH - t.width)),
            (int16)(rand() % (Constants::WINDOW_HEIGHT - t.height)),
            t
        };
        updateVertices(i);
        objects[i].updateUVs((uvs), (objects), i);
    }

    unsigned int VBO, VAO, UBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &UBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 2 * sizeof(int16), 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, UBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0));

    // Texture choord

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // Textures
    stbi_set_flip_vertically_on_load(true);


    shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0].texture);
    glBindVertexArray(VAO);

    // Time
    float time = 0.0f;
    float deltaTime = 0.1f;
    float currentTime = (float)glfwGetTime();
    float lastPrinted = currentTime;
    float accumulator = 0.0f;
    

    // Game

    Pandemonium pandemonium;

    for (uint32 i = 0; i < Constants::OBJECT_COUNT; i++){
        objects[i].x = rand() % (Constants::WINDOW_WIDTH - 5);
        objects[i].y = rand() % (Constants::WINDOW_HEIGHT - 5);
        updateVertices(i);
        
    }



    //std::cout<<vertices[0]/1920.0f<<" "<<vertices[1]/1080.0f<<" "<<
    //    vertices[2]/1920.0f<<" "<<vertices[3]/1080.0f<<" "<<

    //    vertices[4]/1920.0f<<" "<<vertices[5]/1080.0f<<" "<<
    //    vertices[6]/1920.0f<<" "<<vertices[7]/1080.0f<<" "<<
    //    vertices[8]/1920.0f<<" "<<vertices[9]/1080.0f<<" "<<
    //    vertices[10]/1920.0f<<" "<<vertices[11]/1080.0f<<std::endl;;
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    std::cout<<glGetError()<<std::endl;




    while (running)
    {
        if (firstFrame)
        {
            firstFrame = false;
            //Initialize renderer
            
            //Initialize physics
            // Sprites
        }
        else
        {
            // Time
            float newTime = (float)glfwGetTime();
            float frameTime = newTime - currentTime;
            currentTime = newTime;
            
            // Animation update

            // printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

            // Input
            pandemonium.ProcessInput(window, &deltaTime);
            // Gamelogic
            accumulator += frameTime;

            // Rendering


            running = running && !glfwWindowShouldClose(window);
            while (accumulator >= deltaTime)
            {
                glfwPollEvents();
                
                update();
                accumulator -= deltaTime;
                time += deltaTime;
            }
            render();
        }
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &UBO);
    for (Texture i : textures){
        glDeleteTextures(1, &i.texture);
    }
    glfwTerminate();
    return 0;
}    
