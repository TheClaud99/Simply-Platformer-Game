#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


#include "Character.h"
#include "LTexture.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGT = 480;

const float cWalkSpeed = 160.0f;
const float cJumpSpeed = -150.0f;
const float cMinJumpSpeed = 200.0f;
const float cHalfSizeY = 20.0f;
const float cHalfSizeX = 6.0f;



Character c;

SDL_Window* gWindow;
SDL_Renderer* gRenderer;


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

	if(!c.mTexture.loadFromFile("foo.png"))
	{
		success = false;
		cout << "Error loading foo texture " << IMG_GetError() << endl;
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

				SDL_RenderClear(gRenderer);
				
				c.CharacterUpdate();

				SDL_RenderPresent(gRenderer);

				SDL_Delay(10);
			}
		}
	}

	close();

	return 0;
}