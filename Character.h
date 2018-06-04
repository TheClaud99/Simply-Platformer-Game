#ifndef CHARACTER_H
#define CHARACTER_H

#include "movingObject.h"

class Character : public movingObject
{
	public:

		Character();

		bool Relased(SDL_Scancode key);

		bool KeyState(SDL_Scancode key);

		bool Pressed(SDL_Scancode key);

		void CharacterUpdate();

		void UpdatePrevInputs();

		bool mInputs[284];
		bool mPrevInputs[284];

		float mElapsedTime;
};

#endif
