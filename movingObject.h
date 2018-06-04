#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "AABB.h"
#include <cmath>
#include <algorithm>
#include <string>
#include <stdio.h>

#include "LTexture.h"

class movingObject
{
	public:

		movingObject();

		bool Overlaps(AABB other);

		void UpdatePhysics();

		LTexture mTexture;

		//AABB and offset
		AABB mAABB;
		AABB mAABBOffset;

		//Position, speed and scale.
		SDL_Point mPosition;
		SDL_Point mOldPosition;
		Vector mOldSpeed;
		Vector mSpeed;

		//Position state of the object
		bool mPushedRightWall;
		bool mPushesRightWall;

		bool mPushedLeftWall;
		bool mPushesLeftWall;

		bool mWasOnGround;
		bool mOnGround;

		bool mWasAtCeiling;
		bool mAtCeiling;

		CharacterState mCurrentState = CharacterState::Stand;
		float mJumpSpeed;
		float mWalkSpeed;


};

#endif
