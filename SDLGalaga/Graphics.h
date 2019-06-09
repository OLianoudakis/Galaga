#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include<string>
#include <iostream>

using namespace std;

class Graphics
{
public:
    //Window parameters
    static const int SCREEN_WIDTH = 1024;
    static const int SCREEN_HEIGHT = 896;
    const char* WINDOW_TITLE = "Galaga";

private:

    static Graphics* sInstance;
    static bool sInitialized; //true when everything initialized fine

    SDL_Window* mWindow;
    SDL_Surface* mBackBuffer;

    SDL_Renderer* mRenderer;

public:

    static Graphics* Instance(); //returns sInstance
    static void Release(); //clear static memory alloc
    static bool Initialized();

    SDL_Texture* LoadTexture(string path);

    //Prerenders font into texture
    SDL_Texture* CreateTextTexture(TTF_Font* font, string text, SDL_Color color);

    void ClearBackBuffer(); //called at beggining of everyframe to clear canvas

    //draw texture or text
    void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
    //draw lines (used for bezier debug)
    void DrawLine(float startX, float startY, float endX, float endY);

    void Render(); //refresh backbuffer when rdy to draw

private:

    Graphics();
    ~Graphics();

    bool Init();
};


#endif // !_GRAPHICS_H
