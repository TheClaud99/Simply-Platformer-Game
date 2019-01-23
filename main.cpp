#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


#include "Character.h"
#include "LTexture.h"
#include "LTimer.h"
#include "Map.hpp"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGT = 480;

const float cWalkSpeed = 400.0f;
const float cJumpSpeed = -800.0f;
const float cHalfSizeY = 20.0f;
const float cHalfSizeX = 6.0f;


Character c;


SDL_Window* gWindow;
SDL_Renderer* gRenderer;

LTexture gBackGroundTexture;

LTimer stepTimer;
float timeStep = 0;

void CharacterInit()
{

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
		c.gCharacterSpirteClips[ c.Stand ].x = 0;
        c.gCharacterSpirteClips[ c.Stand ].y = 0;
        c.gCharacterSpirteClips[ c.Stand ].w = 40;
        c.gCharacterSpirteClips[ c.Stand ].h = 56;

        //Set top right sprite
        c.gCharacterSpirteClips[ c.Walk ].x = 42;
        c.gCharacterSpirteClips[ c.Walk ].y = 0;
        c.gCharacterSpirteClips[ c.Walk ].w = 44;
        c.gCharacterSpirteClips[ c.Walk ].h = 60;
        
        //Set bottom left sprite
        c.gCharacterSpirteClips[ c.Walk2Frame ].x = 88;
        c.gCharacterSpirteClips[ c.Walk2Frame ].y = 0;
        c.gCharacterSpirteClips[ c.Walk2Frame ].w = 30;
        c.gCharacterSpirteClips[ c.Walk2Frame ].h = 60;

        //Set bottom right sprite
        c.gCharacterSpirteClips[ c.Jump ].x = 121;
        c.gCharacterSpirteClips[ c.Jump ].y = 0;
        c.gCharacterSpirteClips[ c.Jump ].w = 47;
        c.gCharacterSpirteClips[ c.Jump ].h = 60;
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

				timeStep = stepTimer.getTicks() / 1000.f;

				SDL_RenderClear(gRenderer);
				
				gBackGroundTexture.render(START_POSITION.x - c.mPosition.x, START_POSITION.y - c.mPosition.y);

				c.CharacterUpdate();

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