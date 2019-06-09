#include"StartScreen.h"
#include"InputManager.h"

StartScreen::StartScreen()
{
    mTimer = Timer::Instance();

    //Top Bar Entities
    mTopBar = new GameEntity(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 80.0f);
    mPlayer = new Texture("1UP", "emulogic.ttf", 32, {200,0,0});
    mHighScore = new Texture("HI - SCORE", "emulogic.ttf", 32, {200,0,0});
    mPlayerScore = new Scoreboard();
    mTopScore = new Scoreboard();

    mPlayer->Parent(mTopBar);
    mHighScore->Parent(mTopBar);
    mPlayerScore->Parent(mTopBar);
    mTopScore->Parent(mTopBar);

    mPlayer->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH*0.35f, 0.0f));
    mHighScore->Pos(VEC2_ZERO);

    mPlayerScore->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH*0.25f, 40.0f));
    mTopScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.05f, 40.0f));

    mTopScore->Score(30000);

    mTopBar->Parent(this);

    //Logo Entities
    mLogo = new Texture("galagalogo.png", 128, 53, 508, 241);

    mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.55f, Graphics::Instance()->SCREEN_HEIGHT*0.32f));

    mLogo->Parent(this);

    //Play Mode Entities
    mPlayMode = new GameEntity(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.55f);
    mPlayerMode = new Texture("1 Player", "emulogic.ttf", 32, { 230,230,230 });
    mCursor = new Texture("Cursor.png");

    mPlayerMode->Parent(mPlayMode);
    mCursor->Parent(mPlayMode);

    mPlayerMode->Pos(Vector2(-20.0f, -35.0f));
    mCursor->Pos(Vector2(-150.0f, -35.0f));

    mPlayMode->Parent(this);

    //Bottom Bar Entities
    mBotBar = new GameEntity(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.7f);
    mNamco = new Texture("namco", "namco__.ttf", 36, { 200,0,0 });
    mDates = new Texture("1981 1985 NAMCO LTD.", "emulogic.ttf", 32, { 230,230,230 });
    mRights = new Texture("ALL RIGHTS RESERVED", "emulogic.ttf", 32, { 230,230,230 });

    mNamco->Parent(mBotBar);
    mDates->Parent(mBotBar);
    mRights->Parent(mBotBar);

    mNamco->Pos(VEC2_ZERO);
    mDates->Pos(Vector2(0.0f,90.0f));
    mRights->Pos(Vector2(0.0f,170.0f));

    mBotBar->Parent(this);

    //Screen Animation Variables
    ResetAnimation();

    mStars = BackgroundStars::Instance();
    mStars->Scroll(true);
}

StartScreen::~StartScreen()
{
    //Freeing Top Bar Entities
    delete mTopBar;
    mTopBar = NULL;
    delete mPlayer;
    mPlayer = NULL;
    delete mHighScore;
    mHighScore = NULL;
    delete mPlayerScore;
    mPlayerScore = NULL;
    delete mTopScore;
    mTopScore = NULL;

    //Freeing Logo Entities
    delete mLogo;
    mLogo = NULL;

    //Freeing Play Mode Entities
    delete mPlayMode;
    mPlayMode = NULL;
    delete mPlayerMode;
    mPlayerMode = NULL;
    delete mCursor;
    mCursor = NULL;

    //Freeing Bot Bar Entities
    delete mBotBar;
    mBotBar = NULL;
    delete mNamco;
    mNamco = NULL;
    delete mDates;
    mDates = NULL;
    delete mRights;
    mRights = NULL;
}

void StartScreen::ResetAnimation()
{
    mAnimationStartPosition = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
    mAnimationEndPosition = VEC2_ZERO;
    mAnimationTotalTime = 5.0f;
    mAnimationTimer = 0.0f;
    mAnimationDone = false;

    Pos(mAnimationStartPosition);
}

int StartScreen::SelectedMode()
{
    return mSelectedMode;
}

void StartScreen::ChangeSelectedmode(int change)
{
    mSelectedMode += change;

    if (mSelectedMode < 0)
    {
        mSelectedMode = 1;
    }
    else if (mSelectedMode > 1)
    {
        mSelectedMode = 0;
    }

    
}

void StartScreen::Update()
{
    if (!mAnimationDone)
    {
        mAnimationTimer += mTimer->DeltaTime();
        Pos(Lerp(mAnimationStartPosition, mAnimationEndPosition, mAnimationTimer / mAnimationTotalTime));

        if (mAnimationTimer >= mAnimationTotalTime)
        {
            mAnimationDone = true;
            mStars->Scroll(false);
        }       
    }
}

void StartScreen::Render()
{
    mPlayer->Render();
    mHighScore->Render();
    mPlayerScore->Render();
    mTopScore->Render();

    mLogo->Render();
    mCursor->Render();
    mPlayerMode->Render();
    

    mNamco->Render();
    mDates->Render();
    mRights->Render();
}