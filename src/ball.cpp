#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Ball.h"
#include "Entity.h"
#include "Math.h"
#include "configuration.h"

Ball::Ball(Vector2f p_pos, SDL_Texture *p_tex)
    : Entity(p_pos, p_tex)
{
}

void Ball::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}

void Ball::update(double deltaTime)
{
    Vector2f pos = this->getPos();
    Vector2f vel = this->getVelocity();
    SDL_Rect rect = this->getCurrentFrame();
    float dx = vel.x * deltaTime;
    float dy = vel.y * deltaTime;
    pos.x += dx;
    pos.y += dy;
    if (pos.x <= 0)
    {
        setVelocity(abs(vel.x), vel.y);
    }
    else if ((pos.x + rect.w) >= (double)WIDTH)
    {
        setVelocity(-abs(vel.x), vel.y);
    }
    if (pos.y < 0)
    {
        setVelocity(vel.x, abs(vel.y));
    }
    else if ((pos.y + rect.h) > (double)HEIGHT)
    {
        setVelocity(vel.x, -abs(vel.y));
    }
    this->setPos(pos.x, pos.y);
}