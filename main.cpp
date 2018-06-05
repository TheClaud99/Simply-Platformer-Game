#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


#include "Character.h"
#include "LTexture.h"
#include "LTimer.h"

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGT = 720;

const float cWalkSpeed = 400.0f;
const float cJumpSpeed = -500.0f;
const float cHalfSizeY = 20.0f;
const float cHalfSizeX = 6.0f;

SDL_Rect gCharacterSpirteClips[TotalStates + 1];

Character c;

SDL_Window* gWindow;
SDL_Renderer* gRenderer;

LTexture gBackGroundTexture;

LTimer stepTimer;
float timeStep = 0;

void CharacterInit()
{
	c.mAABB.halfsize = {cHalfSizeX, cHalfSizeY};
	c.mAABBOffset.center.y = c.mAABB.halfsize.y;

	c.mJumpSpeed = cJumpSpeed;
	c.mWalkSpeed = cWalkSpeed;

}

bool init()
{
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		success = false;
		cout << "Error initialing SDL libraries " << SDL_GetError() << endl;
	}
	else
	{
		gWindow = SDL_CreateWindow("Platformer game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL)
		{
			success = false;
			cout << "Error creatin the window " << SDL_GetError() << endl;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == NULL)
			{
				success = false;
				cout << "Error initialing renderer " << SDL_GetError() << endl;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imageFlags = IMG_INIT_PNG;

				if(!(IMG_Init(imageFlags) &imageFlags))
				{
					cout << "Error initialing image library " << IMG_GetError() << endl;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	if(!c.mTexture.loadFromFile("images/mario.png"))
	{
		success = false;
		cout << "Error loading foo texture " << IMG_GetError() << endl;
	}
	else
	{
		gCharacterSpirteClips[ Stand ].x = 0;
        gCharacterSpirteClips[ Stand ].y = 0;
        gCharacterSpirteClips[ Stand ].w = 40;
        gCharacterSpirteClips[ Stand ].h = 56;

        //Set top right sprite
        gCharacterSpirteClips[ Walk ].x = 42;
        gCharacterSpirteClips[ Walk ].y = 0;
        gCharacterSpirteClips[ Walk ].w = 44;
        gCharacterSpirteClips[ Walk ].h = 60;
        
        //Set bottom left sprite
        gCharacterSpirteClips[ Walk2Frame ].x = 88;
        gCharacterSpirteClips[ Walk2Frame ].y = 0;
        gCharacterSpirteClips[ Walk2Frame ].w = 30;
        gCharacterSpirteClips[ Walk2Frame ].h = 60;

        //Set bottom right sprite
        gCharacterSpirteClips[ Jump ].x = 121;
        gCharacterSpirteClips[ Jump ].y = 0;
        gCharacterSpirteClips[ Jump ].w = 47;
        gCharacterSpirteClips[ Jump ].h = 60;
    }
	
	if(!gBackGroundTexture.loadFromFile("images/background.png"))
	{
		success = false;
		cout << IMG_GetError() << endl;
	}
	else
	{
		gBackGroundTexture.mWidth = SCREEN_WIDTH;
		gBackGroundTexture.mHeight = SCREEN_HEIGT;
	}

	return success;
}

void close()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	
	SDL_Quit();
	IMG_Quit();
}

int main( int argc, char* args[] )
{
	SDL_Event e;
	bool quit = false;

	if(init())
	{
		if(loadMedia())
		{

			CharacterInit();

			while(!quit)
			{
				while(SDL_PollEvent(&e) != 0)
				{
					if(e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if(e.type == SDL_KEYDOWN)
					{
						c.mInputs[SDL_GetScancodeFromKey(e.key.keysym.sym)] = true;
					}
					else if(e.type == SDL_KEYUP)
					{
						c.mInputs[SDL_GetScancodeFromKey(e.key.keysym.sym)] = false;
					}
				}

				cout << "TimeStep: " << timeStep << endl;
				timeStep = stepTimer.getTicks() / 1000.f;

				SDL_RenderClear(gRenderer);
				
				gBackGroundTexture.render(0, 0);

				c.CharacterUpdate();

				cout << c.mPosition.y << endl;

				stepTimer.start();

				
				SDL_RenderPresent(gRenderer);

				if(timeStep < 1/60.f)
				{
					SDL_Delay(1000 * (1/60.f - timeStep));
				}

			}
		}
	}

	close();

	return 0;
}