#pragma once
#include <SDL2/SDL.h>

#include "Entity.h"
#include "Math.h"

class Ball : public Entity
{
public:
    Ball(Vector2f p_pos, SDL_Texture *p_tex);
    Vector2f &getVelocity()
    {
        return velocity;
    }
    void setVelocity(float x, float y);
    void update(double deltaTime);
    bool isColide(SDL_Rect *paddle);

private:
    Vector2f velocity = Vector2f(0, 0);
};