#ifndef _AUDIOMANAGER_H
#define _AUDIOMANAGER_H
#include "AssetManager.h"

class AudioManager
{
private:
    //singleton instance
    static AudioManager* sInstance;

    AssetManager* mAssetManager;

public:
    //constructor - destructor of singleton
    static AudioManager* Instance();
    static void Release();

    //functionality methods
    void PlayMusic(string filename, int loops = -1);
    void PauseMusic();
    void ResumeMusic();

    void PlaySFX(string filename, int loops = 0, int channel = 0);

private:
    //constructor - destructor of manager
    AudioManager();
    ~AudioManager();
};

#endif // !_AUDIOMANAGER_H

