#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "GameEntity.h"
#include "AssetManager.h"
#include <iostream>

using namespace std;

class Texture : public GameEntity
{

protected:
    //The texture
    SDL_Texture* mTex;

    //Reference to graphics class for render
    Graphics* mGraphics;

    int mWidth;
    int mHeight;

    bool mClipped; //tells if texture is clipped

    //ability to move texture
    SDL_Rect mRenderRect;
    //ability to clip texture
    SDL_Rect mClipRect;

public:
    Texture(string filename);
    Texture(string filename, int x, int y, int w, int h);
    Texture(string text, string fontpath, int size, SDL_Color color);
    ~Texture();

    Vector2 ScaledDimentions();

    virtual void Render();
};
#endif // !_TEXTURE_H

