#include "Graphics.h"
#include<iostream>

using namespace std;

Graphics* Graphics::sInstance = NULL;
bool Graphics::sInitialized = false;

Graphics* Graphics::Instance()
{
    if (sInstance == NULL)
    {
        sInstance = new Graphics();
    }

    return sInstance;
}

void Graphics::Release()
{
    delete sInstance;
    sInstance = NULL;

    sInitialized = false;
}

bool Graphics::Initialized()
{
    return sInitialized;
}

Graphics::Graphics()
{
    mBackBuffer = NULL;

    sInitialized = Init();
}

Graphics::~Graphics()
{
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;

    SDL_DestroyRenderer(mRenderer);
    mRenderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

//initialize Window, backcolor, renderer, img and font functions 
bool Graphics::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        cout << "SDL Init Error: " << endl << SDL_GetError() << endl;
        return false;
    }

    mWindow = SDL_CreateWindow("Galaga", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (mWindow == NULL)
    {
        cout << "SDL Window Creation Error: " << endl << SDL_GetError << endl;
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED); //hardware accelerated
   
    if (mRenderer == NULL)
    {
        cout << "Renderer Creation Error: " << endl << SDL_GetError << endl;
        return false;
    }
    //changed to black
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);

    //init image library for png
    int flags = IMG_INIT_PNG;
    if (!(IMG_Init(flags) & flags))
    {
        cout << "Image Init Error: " << endl << IMG_GetError() << endl;
        return false;
    }

    if (TTF_Init() == -1)
    {
        cout << "TTF Init Error: " << endl << TTF_GetError() << endl;
    }

    mBackBuffer = SDL_GetWindowSurface(mWindow);

    return true;
}

//Load Texture from path
SDL_Texture* Graphics::LoadTexture(string path)
{
    SDL_Texture* tex = NULL;

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL)
    {
        cout << "Image Load Error: " << endl << "Path: " << path.c_str() << "Error: " << IMG_GetError << endl;
        return tex; //which is NULL now
    }

    tex = SDL_CreateTextureFromSurface(mRenderer, surface);
    if (tex == NULL)
    {
        cout << "Create Texture Error: " << endl << SDL_GetError << endl;
        return tex; //is null
    }

    SDL_FreeSurface(surface);

    return tex;
}

//Create font as texture
SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, string text, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == NULL)
    {
        cout << "Text Render Error: " << endl << TTF_GetError() << endl;
        return NULL;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);
    if (tex == NULL)
    {
        cout << "Text Texture Creation Error: " << endl << SDL_GetError() << endl;       
    }

    SDL_FreeSurface(surface);

    return tex;
}

void Graphics::ClearBackBuffer()
{
    SDL_RenderClear(mRenderer);
}
//render texture
void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(mRenderer, tex, clip , rend, angle, NULL, flip);
}
//render lines (used for Bezier Debug)
//new method
void Graphics::DrawLine(float startX, float startY, float endX, float endY)
{
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(mRenderer, startX, startY, endX, endY);
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}
//render screen
void Graphics::Render()
{
    SDL_RenderPresent(mRenderer);
}