#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "BackgroundStars.h"
#include "Scoreboard.h"

//using namespace QuickSDL;

class StartScreen : public GameEntity
{
private:

    Timer* mTimer;

    //top bar
    GameEntity* mTopBar;
    Texture* mPlayer;
    Texture* mHighScore;
    //Texture* mPlayerTwo;
    Scoreboard* mPlayerScore;
    Scoreboard* mTopScore;
    //Scoreboard* mPlayerTwoScore;

    //Logo Entities
    Texture* mLogo;

    //Play mode entities
    GameEntity* mPlayMode;
    Texture* mPlayerMode;
    Texture* mCursor;
    int mSelectedMode;

    //Bottom Bar Entities
    GameEntity* mBotBar;
    Texture* mNamco;
    Texture* mDates;
    Texture* mRights;

    //Screen Animation Variables
    Vector2 mAnimationStartPosition;
    Vector2 mAnimationEndPosition;
    float mAnimationTotalTime;
    float mAnimationTimer;
    bool mAnimationDone;

    BackgroundStars* mStars;

public:

    StartScreen();
    ~StartScreen();

    void ResetAnimation();

    int SelectedMode();

    void ChangeSelectedmode(int change);

    void Update();
    void Render();

};
#endif // !_STARTSCREEN_H

