#include "AudioManager.h"

AudioManager* AudioManager::sInstance = NULL;

AudioManager* AudioManager::Instance()
{
    if (sInstance == NULL)
    {
        sInstance = new AudioManager();
    }

    return sInstance;
}

void AudioManager::Release()
{
    delete sInstance;
    sInstance = NULL;
}

AudioManager::AudioManager()
{
    mAssetManager = AssetManager::Instance();

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
    {
        cout << "Mixer Init Error: " << endl << Mix_GetError() << endl;
    }
}

AudioManager::~AudioManager()
{
    mAssetManager = NULL;
    Mix_Quit();
}

void AudioManager::PlayMusic(string filename, int loops)
{
    Mix_PlayMusic(mAssetManager->GetMusic(filename), loops);
}

void AudioManager::PauseMusic()
{
    if (Mix_PlayingMusic() != 0)
    {
        Mix_PauseMusic();
    }
}

void AudioManager::ResumeMusic()
{
    if (Mix_PausedMusic() != 0)
    {
        Mix_ResumeMusic();
    }
}

void AudioManager::PlaySFX(string filename, int loops, int channel)
{
    Mix_PlayChannel(channel, mAssetManager->GetSFX(filename), loops);
}