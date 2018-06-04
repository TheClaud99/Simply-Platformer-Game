#include "movingObject.h"

movingObject::movingObject()
{

}


bool movingObject::Overlaps(AABB other)
{
	if(abs(mAABB.center.x - other.center.x) > (mAABB.halfsize.x + other.halfsize.x)) return false;
	if(abs(mAABB.center.y - other.center.y) > (mAABB.halfsize.y + other.halfsize.y)) return false;

	return true;
}

void movingObject::UpdatePhysics()
{
	//Save the previous frame's data.
	mOldPosition = mPosition;
	mOldSpeed = mSpeed;

	mWasOnGround = mOnGround;
	mPushedRightWall = mPushesRightWall;
	mPushedLeftWall = mPushesLeftWall;
	mWasAtCeiling = mAtCeiling;

	//Update the position.
	mPosition.x += mSpeed.x * VELOCITY/60;
	mPosition.y += (int)(mSpeed.y * VELOCITY/50);

	//Check if it's on ground.
	if(mPosition.y >= GROUND)
	{
		mPosition.y = GROUND;
		mOnGround = true;
	}
	else
	{
		mOnGround = false;
	}

	//Update the center with the new position.
	mAABB.center.x = mPosition.x + mAABBOffset.center.x;
	mAABB.center.y = mPosition.y + mAABBOffset.center.y;

}
