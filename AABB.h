#include "SDL2/SDL.h"


struct Vector
{
    float x;
    float y;
};

//Axis Aligned Bounding Box, basic an unrotated rectangle
struct AABB
{
	SDL_Point center;
	Vector halfsize;
};

const float GRAVITY = 9.81;
const float MAX_FALLING_SPEED = 150.0;
const float MIN_JUMP_SPEED = -80.0;


const int GROUND = 300;