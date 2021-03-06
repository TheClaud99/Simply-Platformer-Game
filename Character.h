#ifndef CHARACTER_H
#define CHARACTER_H

#include "movingObject.h"

class Character : public movingObject
{
	public:

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

		Character();

		bool Relased(SDL_Scancode key);

		bool KeyState(SDL_Scancode key);

		bool Pressed(SDL_Scancode key);

		void CharacterUpdate();

		void UpdatePrevInputs();

		bool mInputs[284];
		bool mPrevInputs[284];

		float mElapsedTime;

		SDL_RendererFlip mFlip;

		SDL_Rect gCharacterSpirteClips[TotalStates + 1];

		CharacterState mCurrentState = CharacterState::Stand;
};

#endif
