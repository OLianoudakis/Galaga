#include "AssetManager.h"
#include <iostream>

using namespace std;

AssetManager* AssetManager::sInstance = NULL;

AssetManager* AssetManager::Instance()
{
    if (sInstance == NULL)
    {
        sInstance = new AssetManager();
    }

    return sInstance;
}

void AssetManager::Release()
{
    delete sInstance;
    sInstance = NULL;
}

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
    for (auto tex : mTextures)
    {
        if (tex.second != NULL)
        {
            SDL_DestroyTexture(tex.second);
        }
    }
    mTextures.clear();

    for (auto text : mText)
    {
        if (text.second != NULL)
        {
            SDL_DestroyTexture(text.second);
        }
    }

    mText.clear();

    for (auto font : mFonts)
    {
        if (font.second != NULL)
        {
            TTF_CloseFont(font.second);
        }
    }

    mFonts.clear();

    for (auto music : mMusic)
    {
        if (music.second != NULL)
        {
            Mix_FreeMusic(music.second);
        }
    }

    mMusic.clear();

    for (auto sfx : mSFX)
    {
        if (sfx.second != NULL)
        {
            Mix_FreeChunk(sfx.second);
        }
    }

    mSFX.clear();
}

SDL_Texture* AssetManager::GetTexture(string filename)
{
    string fullPath = SDL_GetBasePath();
    fullPath.append("Assets/" + filename);

    if (mTextures[fullPath] == nullptr)
    {
        mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);
    }

    return mTextures[fullPath];
}

TTF_Font* AssetManager::GetFont(string filename, int size)
{
    string fullPath = SDL_GetBasePath();
    fullPath.append("Assets/" + filename);
    string key = fullPath + (char)size; //unique key of filename

    if (mFonts[key] == nullptr)
    {
        mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);
        if (mFonts[key] == nullptr)
        {
            cout << "Font Loading Error: " << endl << "Font: " << filename.c_str() << "Error: " << TTF_GetError() << endl;
        }
    }

    return mFonts[key];
}

SDL_Texture* AssetManager::GetText(string text, string filename, int size, SDL_Color color)
{
    TTF_Font* font = GetFont(filename, size);

    string key = text + filename + (char)size + (char)color.r + (char)color.g + (char)color.b;

    if (mText[key] == nullptr)
    {
        mText[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
    }

    return mText[key];
}

Mix_Music* AssetManager::GetMusic(string filename)
{
    string fullPath = SDL_GetBasePath();
    fullPath.append("Assets/" + filename);

    if (mMusic[fullPath] == nullptr)
    {
        mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());
        if (mMusic[fullPath] == NULL)
        {
            cout << "Music Loading Error: " << endl << "File: " << filename.c_str()<< "Error: " << Mix_GetError() << endl;
        }        
    }

    return mMusic[fullPath];
}

Mix_Chunk* AssetManager::GetSFX(string filename)
{
    string fullPath = SDL_GetBasePath();
    fullPath.append("Assets/" + filename);

    if (mSFX[fullPath] == nullptr)
    {
        mSFX[fullPath] = Mix_LoadWAV(fullPath.c_str());
        if (mSFX[fullPath] == NULL)
        {
            cout << "SFX Loading Error: " << endl << "File" << filename.c_str() << " Error: " << Mix_GetError() << endl;
        }
    }

    return mSFX[fullPath];
}