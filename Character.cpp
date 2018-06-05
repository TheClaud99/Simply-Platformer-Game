#include "Character.h"

Character::Character()
{
    for(int i = 0; i < sizeof(mInputs); i++)
	{
		mInputs[i] = false;
		mPrevInputs[i] = false;
	}
}

bool Character::Relased(SDL_Scancode key)
{
    return (!mInputs[(int)key] && mPrevInputs[(int)key]);
}

bool Character::KeyState(SDL_Scancode key)
{
    return mInputs[(int)key];
}

bool Character::Pressed(SDL_Scancode key)
{
    return (mInputs[key] && !mPrevInputs[key]);
}

void Character::CharacterUpdate()
{
    
    switch(mCurrentState)
    {
        case CharacterState::Stand:

            mTexture.render(mPosition.x, mPosition.y, &gCharacterSpirteClips[Stand], mFlip);
            
            mSpeed = {0.0f, 0.0f};
            
            //If the character isn't on the ground change his state to Jump.
            if(!mOnGround)
            {
                mCurrentState = CharacterState::Jump;
                break;
            }


            //If a movement key is pressed, change the state to Move
            if(KeyState(SDL_SCANCODE_RIGHT) != KeyState(SDL_SCANCODE_LEFT))
            {
                mCurrentState = CharacterState::Walk;
            }

            if(KeyState(SDL_SCANCODE_UP))
            {
                mSpeed.y = mJumpSpeed;
                mCurrentState = CharacterState::Jump;
                break;
            }
            else if(!mOnGround)
            {
                mCurrentState = CharacterState::Jump;
                break;
            }

            break;
        
        case CharacterState::Walk:
            
            

            mElapsedTime += timeStep;

            if(mElapsedTime < FRAME_MOVEMENT_UPDATE_TIME)
            {
                mTexture.render(mPosition.x, mPosition.y, &gCharacterSpirteClips[Walk], mFlip);
            }
            else if(mElapsedTime < 2 * FRAME_MOVEMENT_UPDATE_TIME)
            {
                mTexture.render(mPosition.x, mPosition.y, &gCharacterSpirteClips[Walk2Frame], mFlip);
            }
            else
            {
                mElapsedTime = 0;
            }

            if(KeyState(SDL_SCANCODE_RIGHT) == KeyState(SDL_SCANCODE_LEFT))
            {
                mCurrentState = CharacterState::Stand;
                mSpeed = {0.0f, 0.0f};
                break;
            }
            else if(KeyState(SDL_SCANCODE_RIGHT))
            {
                if(mPushesRightWall)
                {
                    mSpeed.x = 0.0f;
                }
                else
                {
                    mSpeed.x = mWalkSpeed;
                }
            }
            else if(KeyState(SDL_SCANCODE_LEFT))
            {
                if(mPushesLeftWall)
                {
                    mSpeed.x = 0.0f;
                }
                else
                {
                    mSpeed.x = -mWalkSpeed;
                }
            }
            
            if(KeyState(SDL_SCANCODE_UP))
            {
                mSpeed.y = mJumpSpeed;
                mCurrentState = CharacterState::Jump;
                break;
            }
            else if(!mOnGround)
            {
                mCurrentState = CharacterState::Jump;
                break;
            }

            break;

        case CharacterState::Jump:

            mTexture.render(mPosition.x, mPosition.y, &gCharacterSpirteClips[Jump], mFlip);
            mSpeed.y += GRAVITY * timeStep;
            mSpeed.y = std::min(mSpeed.y, MAX_FALLING_SPEED);

            if(KeyState(SDL_SCANCODE_RIGHT) == KeyState(SDL_SCANCODE_LEFT))
            {
                mSpeed.x = 0.0f;
            }
            else if(KeyState(SDL_SCANCODE_RIGHT))
            {
                if(mPushesRightWall)
                {
                    mSpeed.x = 0.0f;
                }
                else
                {
                    mSpeed.x = mWalkSpeed;
                }
            }
            else if(KeyState(SDL_SCANCODE_LEFT))
            {
                if(mPushesLeftWall)
                {
                    mSpeed.x = 0.0f;
                }
                else
                {
                    mSpeed.x = -mWalkSpeed;
                }
            }
            
            //if the jump key is not pressed, the jump speed is decreased
            if(!KeyState(SDL_SCANCODE_UP) && mSpeed.y < 0.0f)
            {
                mSpeed.y = std::max(mSpeed.y, MIN_JUMP_SPEED);
            }

            if(mOnGround)
            {
                mCurrentState = CharacterState::Stand;
            }

            break;

        case CharacterState::GrabLedge:
            break;
    }

    if(mSpeed.x < 0)
    {
        mFlip = SDL_FLIP_HORIZONTAL;
    }
    else if(mSpeed.x > 0)
    {
        mFlip = SDL_FLIP_NONE;
    }

    UpdatePhysics();

    /*printf("\n Position: %d", mPosition.y);
    printf("\n Speed: %f", mSpeed.y);*/
    UpdatePrevInputs();
}


void Character::UpdatePrevInputs()
{
    for(int i = 0; i < SDLK_z; i++)
    {
        mPrevInputs[i] = mInputs[i];
    }
}