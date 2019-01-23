#include "SDL2/SDL.h"


const int LEVEL_WIDTH = 1200;
const int LEVEL_HEIGHT = 960;

struct Vector
{
    float x;
    float y;
};

//Axis Aligned Bounding Box, basic an unrotated rectangle
struct AABB
{
	SDL_Point center;
	SDL_Point halfsize;
};

const float GRAVITY = 1400.0f;
const float MAX_FALLING_SPEED = 1500.0f;
const float MIN_JUMP_SPEED = -400.0f;
const float FRAME_MOVEMENT_UPDATE_TIME = 0.25f;

const SDL_Point START_POSITION = {320, 240};

extern float timeStep;

const int GROUND = 250;