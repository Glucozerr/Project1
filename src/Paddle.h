#pragma once
#include <SDL2/SDL.h>

#include "Entity.h"
#include "Math.h"

class Paddle : public Entity
{
public:
    Paddle(Vector2f p_pos, SDL_Texture *p_tex, int index);
    Vector2f &getVelocity()
    {
        return velocity;
    }
    int getPoint()
    {
        return point;
    }
    void setVelocity(float x, float y);
    void setVelocityX(float x);
    void setVelocityY(float y);
    void addPoint(int p);
    void update(double deltaTime);

private:
    Vector2f velocity = Vector2f(0, 0);
    int point = 0;
    int index;
};