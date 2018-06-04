#ifndef LTEXTURE_H
#define LTEXTURE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <string>

#include "globals.h"

class LTexture
{
	public:
		LTexture();
		~LTexture();

		bool loadFromFile(std::string path);

		void render(int x, int y, SDL_Rect* clip = NULL);

		void free();

		int getWidth();
		int getHeight();

	protected:
		int mWidth;
		int mHeight;
		SDL_Texture* mTexture;
};

#endif
