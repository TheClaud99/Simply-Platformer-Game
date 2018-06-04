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

const float GRAVITY = 700.0f;
const float MAX_FALLING_SPEED = 1000.0f;
const float MIN_JUMP_SPEED = -400.0f;
const float VELOCITY = 1.0f;
const float FRAME_MOVEMENT_UPDATE_TIME = 0.25f;

extern float timeStep;

const int GROUND = 600;

//The possibles Character's state
enum CharacterState
{
    Stand,
    Walk,
    Jump,
    GrabLedge,
    TotalStates
};

const int Walk2Frame = TotalStates;

extern SDL_Rect gCharacterSpirteClips[];