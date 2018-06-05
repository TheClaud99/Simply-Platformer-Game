#include "LTexture.h"

LTexture::LTexture()
{
    free();
}

LTexture::~LTexture()
{
    free();
}

void LTexture::free()
{
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
    }

    mWidth = 0;
    mHeight = 0;
}

bool LTexture::loadFromFile(std::string path)
{
    bool success = true;

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        success = false;
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));

        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture != NULL)
        {
            mTexture = newTexture;

            mWidth = loadedSurface -> w;
            mHeight = loadedSurface -> h;
        }
        
    }

    SDL_FreeSurface(loadedSurface);

    return success;
}

void LTexture::render(int x, int y, SDL_Rect* clip, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if(clip != NULL)
    {
        renderQuad.w = clip -> w;
        renderQuad.h = clip -> h;
    }

    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, 0.0, NULL, flip);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}