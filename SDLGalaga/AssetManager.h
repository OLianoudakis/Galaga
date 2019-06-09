#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H
#include "Graphics.h"
#include <SDL_mixer.h>
#include <map>

using namespace std;

class AssetManager
{
private:
    static AssetManager* sInstance;

    map<string, SDL_Texture*> mTextures;
    map<string, SDL_Texture*> mText;
    map<string, TTF_Font*> mFonts;
    map<string, Mix_Music*> mMusic;
    map<string, Mix_Chunk*> mSFX;

public:
    static AssetManager* Instance();
    static void Release();

    SDL_Texture* GetTexture(string filename);
    SDL_Texture* GetText(string tex, string filename, int size, SDL_Color color);

    Mix_Music* GetMusic(string filename);
    Mix_Chunk* GetSFX(string filename);

private:
    AssetManager();
    ~AssetManager();

    TTF_Font* GetFont(string filename, int size);
};
#endif // !_ASSETMANAGER_H
