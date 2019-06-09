#include"PlaySideBar.h"

PlaySideBar::PlaySideBar()
{
    mTimer = Timer::Instance();
    mAudio = AudioManager::Instance();

    //black background for sidebar
    mBackground = new Texture("background.png");
    mBackground->Parent(this);
    mBackground->Pos(Vector2(45.0f, 380.0f));
    mBackground->Scale(Vector2(3.0f, 10.0f));

    //set textures and fonts for sidebar
    mHighLabel = new Texture("HIGH", "emulogic.ttf", 32, { 150,0,0 });
    mHighLabel->Parent(this);
    mHighLabel->Pos(Vector2(-25.0f, 0.0f));

    mScoreLabel = new Texture("SCORE", "emulogic.ttf", 32, { 150,0,0 });
    mScoreLabel->Parent(this);
    mScoreLabel->Pos(Vector2(25.0f, 32.0f));

    mHighScoreboard = new Scoreboard();
    mHighScoreboard->Parent(this);
    mHighScoreboard->Pos(Vector2(90.0f, 64.0f));

    mPlayerLabel = new Texture("1UP", "emulogic.ttf", 32, { 150,0,0 });
    mPlayerLabel->Parent(this);
    mPlayerLabel->Pos(Vector2(-45.0f, 160.0f));

    //make textures flash
    mBlinkTimer = 0.0f;
    mBlinkInterval = 0.5f;
    mPlayerLabelVisible = true;

    mPlayerScore = new Scoreboard();
    mPlayerScore->Parent(this);
    mPlayerScore->Pos(Vector2(90.0f, 192.0f));

    //player lives represented with ships
    mShips = new GameEntity();
    mShips->Parent(this);
    mShips->Pos(Vector2(-40.0f, 420.0f));

    for (int i = 0; i < MAX_SHIP_TEXTURES; ++i)
    {
        mShipTextures[i] = new Texture("mainShip.png");
        mShipTextures[i]->Parent(mShips);
        mShipTextures[i]->Pos(Vector2(62.0f * (i % 3), 70.0f * (i / 3)));
    }

    mTotalShipsLabel = new Scoreboard();
    mTotalShipsLabel->Parent(mShips);
    mTotalShipsLabel->Pos(Vector2(140.0f, 70.0f));

    mFlags = new GameEntity();
    mFlags->Parent(this);
    mFlags->Pos(Vector2(-50.0f, 650.0f));

    mFlagTimer = 0.0f;
    mFlagInterval = 0.2f;
}

PlaySideBar::~PlaySideBar()
{
    mTimer = NULL;
    mAudio = NULL;

    delete mBackground;
    mBackground = NULL;

    delete mHighLabel;
    mHighLabel = NULL;

    delete mScoreLabel;
    mScoreLabel = NULL;

    delete mHighScoreboard;
    mHighScoreboard = NULL;

    delete mPlayerLabel;
    mPlayerLabel = NULL;
    delete mPlayerScore;
    mPlayerScore = NULL;

    delete mShips;
    mShips = NULL;

    for (int i = 0; i < MAX_SHIP_TEXTURES; ++i)
    {
        delete mShipTextures[i];
        mShipTextures[i] = NULL;
    }

    delete mTotalShipsLabel;
    mTotalShipsLabel = NULL;

    delete mFlags;
    mFlags = NULL;

    ClearFlags();
}

void PlaySideBar::ClearFlags()
{
    for (int i = 0; i < mFlagTextures.size(); ++i)
    {
        delete mFlagTextures[i];
        mFlagTextures[i] = NULL;
    }

    mFlagTextures.clear();
}

void PlaySideBar::AddNextFlag()
{
    //level progression represented with flags
    if (mRemainingLevels >= 50)
    {
        AddFlag("fiftylevelflag.png", 62.0f, 50);
    }
    else if (mRemainingLevels >= 30)
    {
        AddFlag("thirtylevelflag.png", 62.0f, 30);
    }
    else if (mRemainingLevels >= 20)
    {
        AddFlag("twentylevelflag.png", 62.0f, 20);
    }
    else if (mRemainingLevels >= 10)
    {
        AddFlag("tenlevelflag.png", 54.0f, 10);
    }
    else if (mRemainingLevels >= 5)
    {
        AddFlag("fivelevelflag.png", 30.0f, 5);
    }
    else
    {
        AddFlag("onelevelflag.png", 30.0f, 1);
    }
}

//spawn flags in order
void PlaySideBar::AddFlag(std::string filename, float width, int value)
{
    int index = mFlagTextures.size();

    if(index > 0)
        mFlagXOffset += width * 0.5f;

    mRemainingLevels -= value;
    mFlagTextures.push_back(new Texture(filename));
    mFlagTextures[index]->Parent(mFlags);
    mFlagTextures[index]->Pos(VEC2_RIGHT * mFlagXOffset);
    mFlagXOffset += width * 0.5f;

    mAudio->PlaySFX("flagSound.wav");
}

void PlaySideBar::SetHightScore(int score)
{
    mHighScoreboard->Score(score);
}

int PlaySideBar::GetHighScore()
{
    return mHighScoreboard->GetScore();
}

void PlaySideBar::SetPlayerScore(int score)
{
    mPlayerScore->Score(score);
}

void PlaySideBar::SetShips(int ships)
{
    mTotalShips = ships;

    if (ships > MAX_SHIP_TEXTURES)
    {
        mTotalShipsLabel->Score(ships);
    }
}

void PlaySideBar::SetLevel(int level)
{
    ClearFlags();

    mRemainingLevels = level;
    mFlagXOffset = 0.0f;
}

void PlaySideBar::Update()
{
    mBlinkTimer += mTimer->DeltaTime();
    if (mBlinkTimer >= mBlinkInterval)
    {
        mPlayerLabelVisible = !mPlayerLabelVisible;
        mBlinkTimer = 0.0f;
    }

    if (mRemainingLevels > 0)
    {
        mFlagTimer += mTimer->DeltaTime();
        if (mFlagTimer >= mFlagInterval)
        {
            AddNextFlag();
            mFlagTimer = 0.0f;
        }
    }
}

void PlaySideBar::Render()
{
    mBackground->Render();

    mHighLabel->Render();
    mScoreLabel->Render();
    mHighScoreboard->Render();

    if (mPlayerLabelVisible)
    {
        mPlayerLabel->Render();
    }
    mPlayerScore->Render();

    for (int i = 0; i < MAX_SHIP_TEXTURES && i < mTotalShips; ++i)
    {
        mShipTextures[i]->Render();
    }

    if (mTotalShips > MAX_SHIP_TEXTURES)
    {
        mTotalShipsLabel->Render();
    }

    for (int i = 0; i < mFlagTextures.size(); ++i)
    {
        mFlagTextures[i]->Render();
    }
}