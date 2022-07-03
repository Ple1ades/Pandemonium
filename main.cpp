
#include "MapGen.cpp"
#include "Render.cpp"
#include "Physics.cpp"
#include "Input.cpp"
#undef main

#ifndef UTILITIES_H
#include "Utilities.h"
#endif

int main()
{
    // Game Loop
    bool running = true;
    bool firstFrame = true;
    // Physics
    b2Vec2 Gravity(0.0f, 9.8f);
    b2World World(Gravity);
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = World.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody -> CreateFixture(&groundBox, 0.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = World.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body -> CreateFixture(&fixtureDef);
    
    // Graphics
    SDL_Window * window = nullptr;
    SDL_GLContext context;
    // Time
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    float deltaTime = 0;

    while (running)
    {
        if (firstFrame)
        {
            firstFrame = false;

            //Initialize renderer
            if (Render::initialize(window, &context) != 0){
                return 1;
            }
            //Initialize physics
            // Sprites
        }
        else
        {
            // Animation update
            // Physics update
            World.Step(deltaTime, g_kVelocityIterations, g_kPositionIterations);
            b2Vec2 position = body->GetPosition();
            float angle = body->GetAngle();
            // printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

            // Input
            getInput(&running);
            // Gamelogic

            // Time

            LAST = NOW;
            NOW = SDL_GetPerformanceCounter();
            deltaTime = (float)((NOW - LAST)*1000 / (float)SDL_GetPerformanceFrequency() );

            // Rendering
            SDL_GL_SwapWindow(window);
        }
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}