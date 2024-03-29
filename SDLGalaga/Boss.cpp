#include"Boss.h"
#include"BoxCollider.h"
#include "AudioManager.h"

std::vector<std::vector<Vector2>> Boss::sDivePaths;

void Boss::CreateDivePaths()
{
    int currentPath = 0;
    BezierPath* path = new BezierPath();
    //create a dive path
    path->AddCurve({ Vector2(0.0f,0.0f), Vector2(0.0f,-60.0f), Vector2(-90.0f, -60.0f),Vector2(-90.0f, 0.0f) }, 15);
    path->AddCurve({ Vector2(-90.0f,0.0f), Vector2(-90.0f,60.0f), Vector2(-100.0f, 275.0f),Vector2(-15.0f, 275.0f) }, 15);
    path->AddCurve({ Vector2(-15.0f,275.0f), Vector2(85.0f,275.0f), Vector2(85.0f, 125.0f),Vector2(-15.0f, 125.0f) }, 15);
    path->AddCurve({ Vector2(-15.0f,125.0f), Vector2(-175.0f,125.0f), Vector2(0.0f, 450.0f),Vector2(120.0f, 450.0f) }, 25);
    path->AddCurve({ Vector2(120.0f,450.0f), Vector2(160.0f,450.0f), Vector2(200.0f, 500.0f),Vector2(200.0f, 550.0f) }, 15);
    path->AddCurve({ Vector2(200.0f,550.0f), Vector2(200.0f,540.0f), Vector2(200.0f, 810.0f),Vector2(200.0f, 800.0f) }, 1);

    //store it
    sDivePaths.push_back(std::vector<Vector2>());
    path->Sample(&sDivePaths[currentPath]);
    delete path;

    currentPath = 1;
    path = new BezierPath();

    path->AddCurve({ Vector2(0.0f,0.0f), Vector2(0.0f,-60.0f), Vector2(90.0f, -60.0f),Vector2(90.0f, 0.0f) }, 15);
    path->AddCurve({ Vector2(90.0f,0.0f), Vector2(90.0f,60.0f), Vector2(100.0f, 275.0f),Vector2(15.0f, 275.0f) }, 15);
    path->AddCurve({ Vector2(15.0f,275.0f), Vector2(-85.0f,275.0f), Vector2(-85.0f, 125.0f),Vector2(15.0f, 125.0f) }, 15);
    path->AddCurve({ Vector2(15.0f,125.0f), Vector2(175.0f,125.0f), Vector2(0.0f, 450.0f),Vector2(-120.0f, 450.0f) }, 25);
    path->AddCurve({ Vector2(-120.0f,450.0f), Vector2(-160.0f,450.0f), Vector2(-200.0f, 500.0f),Vector2(-200.0f, 550.0f) }, 15);
    path->AddCurve({ Vector2(-200.0f,550.0f), Vector2(-200.0f,540.0f), Vector2(-200.0f, 810.0f),Vector2(-200.0f, 800.0f) }, 1);

    sDivePaths.push_back(std::vector<Vector2>());
    path->Sample(&sDivePaths[currentPath]);
    delete path;

    currentPath = 2;
    path = new BezierPath();

    path->AddCurve({ Vector2(0.0f,0.0f), Vector2(0.0f,-60.0f), Vector2(-90.0f, -60.0f),Vector2(-90.0f, 0.0f) }, 15);
    path->AddCurve({ Vector2(-90.0f,0.0f), Vector2(-90.0f,60.0f), Vector2(100.0f, 340.0f),Vector2(100.0f, 400.0f) }, 15);

    sDivePaths.push_back(std::vector<Vector2>());
    path->Sample(&sDivePaths[currentPath]);
    delete path;

    currentPath = 3;
    path = new BezierPath();

    path->AddCurve({ Vector2(0.0f,0.0f), Vector2(0.0f,-60.0f), Vector2(90.0f, -60.0f),Vector2(90.0f, 0.0f) }, 15);
    path->AddCurve({ Vector2(90.0f,0.0f), Vector2(90.0f,60.0f), Vector2(-100.0f, 340.0f),Vector2(-100.0f, 400.0f) }, 15);

    sDivePaths.push_back(std::vector<Vector2>());
    path->Sample(&sDivePaths[currentPath]);
    delete path;
}

Boss::Boss(int index, int path, bool challengeStage)
    : Enemy(index, path, challengeStage)
{
    //the two textures used in the flapping animation of boss
    mTextures[0] = new Texture("boss.png");
    mTextures[0]->Parent(this);
    mTextures[0]->Pos(VEC2_ZERO);
    
    mTextures[1] = new Texture("boss2.png");
    mTextures[1]->Parent(this);
    mTextures[1]->Pos(VEC2_ZERO);

    mType = boss;

    mCaptureDive = false;
    mCurrentPath = 1;
    mCapturing = false;

    //capture beam init
    mCaptureBeam = new CaptureBeam();
    mCaptureBeam->Parent(this);
    mCaptureBeam->Pos(Vector2(0.0f, -190.0f));
    mCaptureBeam->Rotation(180.0f);

    //Collider Addition
    AddCollider(new BoxCollider(mTextures[1]->ScaledDimentions()));

    mWasHit = false;
}

Boss::~Boss()
{
    delete mCaptureBeam;
    mCaptureBeam = NULL;
}

Vector2 Boss::LocalFormationPosition()
{
    //formation placement depending on Index (common in all boss type objects)
    Vector2 retVal;

    retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 2 * (mIndex / 2)) * pow(-1, mIndex % 2 + 1);
    retVal.y = -sFormation->GridSize().y;

    return retVal;
}

//spawn capture beam
void Boss::HandleCaptureBeam()
{
    mCaptureBeam->Update();

    if (!mCaptureBeam->IsAnimating())
    {
        Translate(VEC2_UP * mSpeed * mTimer->DeltaTime(), world);
        if (Pos().y >= 910.0f)
        {
            Pos(Vector2(WorldFormationPosition().x, -20.0f));
            mCapturing = false;
        }
    }
}

//init dive path follow
void Boss::HandleDiveState()
{
    if (mCurrentWaypoint < sDivePaths[mCurrentPath].size())
    {
        Vector2 waypointPos = mDiveStartPosition + sDivePaths[mCurrentPath][mCurrentWaypoint];

        Vector2 dist = waypointPos - Pos();
        Translate(dist.Normalized() * mTimer->DeltaTime() * mSpeed, world);

        Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

        if ((waypointPos - Pos()).MagnitudeSqr() < EPSILON)
        {
            mCurrentWaypoint++;
        }

        if (mCurrentWaypoint == sDivePaths[mCurrentPath].size())
        {
            if (mCaptureDive)
            {
                mCapturing = true;
                Rotation(180.0f);
            }
            else
            {
                Pos(Vector2(WorldFormationPosition().x, -20.0f));
            }
        }
    }
    else
    {
        //Dive over go back to formation
        if (!mCaptureDive || !mCapturing)
        {
            Vector2 dist = WorldFormationPosition() - Pos();
            Translate(dist.Normalized() * mTimer->DeltaTime() * mSpeed, world);

            Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

            if (dist.MagnitudeSqr() < EPSILON)
            {
                JoinFormation();
            }
        }
        else
        {
            HandleCaptureBeam();
        }
    }
}

void Boss::RenderDiveState()
{
    mTextures[0]->Render();

    /*for (int i = 0; i < sDivePaths[mCurrentPath].size() - 1; ++i)
    {
        Graphics::Instance()->DrawLine(mDiveStartPosition.x + sDivePaths[mCurrentPath][i].x, mDiveStartPosition.y + sDivePaths[mCurrentPath][i].y,
            mDiveStartPosition.x + sDivePaths[mCurrentPath][i + 1].x, mDiveStartPosition.y + sDivePaths[mCurrentPath][i + 1].y);
    }*/

    if (mCapturing && mCaptureBeam->IsAnimating())
    {
        mCaptureBeam->Render();
    }
}

void Boss::Dive(int type)
{
    //init dive state
    mCaptureDive = type != 0;

    Enemy::Dive();

    if (mCaptureDive)
    {
        mCapturing = false;
        mCurrentPath = 2 + rand() % 2;
        mCaptureBeam->ResetAnimation();
    }
    else
    {
        mCurrentPath = mIndex % 2;
    }
}

void Boss::Hit(PhysicsEntity* other)
{
    if (mWasHit)
    {
        //destroy object
        AudioManager::Instance()->PlaySFX("bossgalaga_destroyed.wav", 0, 1);
        sPlayer->AddScore(mCurrentState == Enemy::formation ? 150 : mCaptureDive ? 400 : 800);
        Enemy::Hit(other);
    }
    else
    {
        //injure boss change textures
        mWasHit = true;
        delete mTextures[0];
        mTextures[0] = new Texture("bosshit.png");
        mTextures[0]->Parent(this);
        mTextures[0]->Pos(VEC2_ZERO);
        mTextures[0]->Rotation(0.0f);
        
        delete mTextures[1];
        mTextures[1] = new Texture("bosshit2.png");
        mTextures[1]->Parent(this);
        mTextures[1]->Pos(VEC2_ZERO);
        mTextures[1]->Rotation(0.0f);

        AudioManager::Instance()->PlaySFX("bossgalaga_injured.wav", 0, 2);
    }
}