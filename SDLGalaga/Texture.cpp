#include "Texture.h"
#include <iostream>

using namespace std;

//load texture raw
Texture::Texture(string filename)
{
    mGraphics = Graphics::Instance();

    mTex = AssetManager::Instance()->GetTexture(filename);

    SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

    mClipped = false;

    mRenderRect.w = mWidth;
    mRenderRect.h = mHeight;
}

//load texture with clip
Texture::Texture(string filename, int x, int y, int w, int h)
{
    mGraphics = Graphics::Instance();

    mTex = AssetManager::Instance()->GetTexture(filename);

    mClipped = true;

    mWidth = w;
    mHeight = h;

    mRenderRect.w = mWidth;
    mRenderRect.h = mHeight;

    mClipRect.x = x;
    mClipRect.y = y;
    mClipRect.w = mWidth;
    mClipRect.h = mHeight;
}

//Load font texture
Texture::Texture(string text, string fontpath, int size, SDL_Color color)
{
    mGraphics = Graphics::Instance();
    mTex = AssetManager::Instance()->GetText(text, fontpath, size, color);

    mClipped = false;

    SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

    mRenderRect.w = mWidth;
    mRenderRect.h = mHeight;
}
//Deconstructor
Texture::~Texture()
{
    mTex = NULL;
    mGraphics = NULL;
}
//return dimentions of texture with scaling into consideration 
//(used for creating box colliders with textures)
//new method
Vector2 Texture::ScaledDimentions()
{
    Vector2 scaledDimentions = Scale();
    scaledDimentions.x *= mWidth;
    scaledDimentions.y *= mHeight;

    return scaledDimentions;
}

void Texture::Render()
{
    //possible through GameEntity inheritage
    //take position at center of Texture
    Vector2 pos = Pos(world);
    Vector2 scale = Scale(world);


    mRenderRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
    mRenderRect.y = (int)(pos.y - mHeight * scale.y * 0.5f);
    mRenderRect.w = (int)(mWidth * scale.x);
    mRenderRect.h = (int)(mHeight * scale.y);

    mGraphics->DrawTexture(mTex, (mClipped)? &mClipRect : NULL, &mRenderRect, Rotation(world));
}