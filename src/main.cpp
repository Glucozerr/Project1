#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Math.h"
#include "Clock.h"
#include "Entity.h"
#include "Ball.h"
#include "Paddle.h"
#include "GameManager.h"

#include "configuration.h"



GameManager manager("BTL2-Pong", WIDTH, HEIGHT);

TTF_Font *font;
bool running;

// Load Texture
SDL_Texture *bgTexture = manager.loadTexture("assets/bg_off2.png");
SDL_Texture *ballTexture = manager.loadTexture("assets/ball_off.gif");
SDL_Texture *paddleTexture1 = manager.loadTexture("assets/paddle1.png");
SDL_Texture *paddleTexture2 = manager.loadTexture("assets/paddle2.png");

// Create Entities
Clock timmer = Clock();
Ball ball(Vector2f(WIDTH / 2 - 25, HEIGHT / 2 - 25), ballTexture);
Paddle paddle1(Vector2f(0, HEIGHT / 2 - 75), paddleTexture1, 0);
Paddle paddle2(Vector2f(WIDTH - 50, HEIGHT / 2 - 75), paddleTexture2, 1);

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime;

void closeApp()
{
    manager.cleanUp();
    TTF_CloseFont(font);
    SDL_DestroyTexture(bgTexture);
    SDL_DestroyTexture(ballTexture);
    SDL_Quit();
    TTF_Quit();
}

void update()
{
    Uint32 currentTick = SDL_GetTicks64();
    double deltaTime = (double)(currentTick - lastTick);
    lastTick = currentTick;
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            running = false;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_SPACE)
            {
                ball.setVelocity(0.25, 0.25);
            }
            else if (e.key.keysym.sym == SDLK_w)
            {
                paddle1.setVelocityY(-0.5);
            }
            else if (e.key.keysym.sym == SDLK_s)
            {
                paddle1.setVelocityY(0.5);
            }
            else if (e.key.keysym.sym == SDLK_a)
            {
                paddle1.setVelocityX(-0.5);
            }
            else if (e.key.keysym.sym == SDLK_d)
            {
                paddle1.setVelocityX(0.5);
            }
            else if (e.key.keysym.sym == SDLK_UP)
            {
                paddle2.setVelocity(0, -0.5);
            }
            else if (e.key.keysym.sym == SDLK_DOWN)
            {
                paddle2.setVelocity(0, 0.5);
            }
        }
        else if (e.type == SDL_KEYUP)
        {
            if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_s)
            {
                paddle1.setVelocityY(0);
            }
            else if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_d)
            {
                paddle1.setVelocityX(0);
            }
            else if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN)
            {
                paddle2.setVelocityY(0);
            }
        }
    }
    paddle1.update(deltaTime);
    paddle2.update(deltaTime);
    ball.update(deltaTime);
}

void render()
{
    manager.clear();
    manager.renderBackground(bgTexture);
    manager.render(ball);
    manager.render(paddle1);
    manager.render(paddle2);
    manager.display();
};

int main(int argc, char *argv[])
{
    running = true;
    timmer.start();
    while (running)
    {
        update();
        render();
    }
    closeApp();
    return 0;
}