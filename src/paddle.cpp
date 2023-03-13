#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Paddle.h"
#include "Entity.h"
#include "Math.h"
#include "configuration.h"

Paddle::Paddle(Vector2f p_pos, SDL_Texture *p_tex, int index)
    : Entity(p_pos, p_tex)
{
    this->index = index;
}

void Paddle::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}
void Paddle::setVelocityX(float x)
{
    velocity.x = x;
}
void Paddle::setVelocityY(float y)
{
    velocity.y = y;
}

void Paddle::update(double deltaTime)
{
    Vector2f pos = this->getPos();
    Vector2f vel = this->getVelocity();
    SDL_Rect rect = this->getCurrentFrame();
    float dx = vel.x * deltaTime;
    float dy = vel.y * deltaTime;
    pos.x += dx;
    pos.y += dy;
    if ((this->index == 0 && pos.x <= 0))
    {
        pos.x = 0;
    }
    else if ((this->index == 0 && (pos.x + rect.w) > WIDTH / 2 - 1))
    {
        pos.x = WIDTH / 2 - 1 - rect.w;
    }
    else if ((this->index == 1 && pos.x < WIDTH / 2 - 1))
    {
        pos.x = WIDTH / 2 - 1;
    }
    else if (this->index == 1 && (pos.x + rect.w) < (double)WIDTH)
    {
        pos.x = (WIDTH / 2 - 1);
    }

    if (pos.y < 0)
    {
        pos.y = 0;
    }
    else if ((pos.y + rect.h) > (double)HEIGHT)
    {
        pos.y = HEIGHT - rect.h;
    }
    this->setPos(pos.x, pos.y);
}