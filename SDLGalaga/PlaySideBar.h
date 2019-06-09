#ifndef _PLAYSIDEBAR_H
#define _PLAYSIDEBAR_H
#include "Timer.h"
#include "Scoreboard.h"
#include "AudioManager.h"

class PlaySideBar : public GameEntity
{
private:

    Timer* mTimer;
    AudioManager* mAudio;

    Texture* mBackground;

    Texture* mHighLabel;
    Texture* mScoreLabel;
    Scoreboard* mHighScoreboard;

    Texture* mPlayerLabel;
    float mBlinkTimer;
    float mBlinkInterval;
    bool mPlayerLabelVisible;
    Scoreboard* mPlayerScore;

    static const int MAX_SHIP_TEXTURES = 5;
    GameEntity* mShips;
    Texture* mShipTextures[MAX_SHIP_TEXTURES];
    Scoreboard* mTotalShipsLabel;
    int  mTotalShips;

    GameEntity* mFlags;
    std::vector<Texture*> mFlagTextures;
    int mRemainingLevels;
    int mFlagXOffset;
    float mFlagTimer;
    float mFlagInterval;

private:

    void ClearFlags();
    void AddNextFlag();
    void AddFlag(std::string filename, float width, int value);

public:

    PlaySideBar();
    ~PlaySideBar();

    void SetHightScore(int score);
    int GetHighScore();
    void SetPlayerScore(int score);
    void SetShips(int ships);
    void SetLevel(int level);

    void Update();
    void Render();
};

#endif // !_PLAYSIDEBAR_H

