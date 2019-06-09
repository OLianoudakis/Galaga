#include "Enemy.h"
#include "PhysicsManager.h"

std::vector<std::vector<Vector2>> Enemy::sPaths;
Formation* Enemy::sFormation = NULL;
Player* Enemy::sPlayer = nullptr;

//create spawn paths
void Enemy::CreatePaths()
{
    int screenMidPoint = Graphics::Instance()->SCREEN_WIDTH * 0.4f;

    int currentPath = 0;
    BezierPath* path = new BezierPath();
    path->AddCurve({ Vector2(screenMidPoint + 50.0f, -10.0f), Vector2(screenMidPoint + 50.0f , -20.0f), Vector2(screenMidPoint + 50.0f, 30.0f), Vector2(screenMidPoint + 50.0f, 20.0f) }, 1);
    path->AddCurve({ Vector2(screenMidPoint + 50.0f, 20.0f), Vector2(screenMidPoint + 50.0f, 100.0f), Vector2(75.0f, 325.0f), Vector2(75.0f, 425.0f) }, 25);
    path->AddCurve({ Vector2(75.0f, 425.0f), Vector2(75.0f, 650.0f), Vector2(350.0f, 650.0f), Vector2(350.0f, 425.0f) }, 25);
    
    sPaths.push_back(std::vector<Vector2>());
    path->Sample(&sPaths[currentPath]);
    delete path;

    currentPath = 1;
    path = new BezierPath();
    int fullScreen = screenMidPoint * 2;
    path->AddCurve({ Vector2(screenMidPoint - 50.0f, -10.0f), Vector2(screenMidPoint - 50.0f , -20.0f), Vector2(screenMidPoint - 50.0f, 30.0f), Vector2(screenMidPoint - 50.0f, 20.0f) }, 1);
    path->AddCurve({ Vector2(screenMidPoint - 50.0f, 20.0f), Vector2(screenMidPoint - 50.0f, 100.0f), Vector2(fullScreen - 75.0f, 325.0f), Vector2(fullScreen - 75.0f, 425.0f) }, 25);
    path->AddCurve({ Vector2(fullScreen - 75.0f, 425.0f), Vector2(fullScreen - 75.0f, 650.0f), Vector2(fullScreen - 350.0f, 650.0f), Vector2(fullScreen - 350.0f, 425.0f) }, 25);

    sPaths.push_back(std::vector<Vector2>());
    path->Sample(&sPaths[currentPath]);
    delete path;

    currentPath = 2;
    path = new BezierPath();
    int temp = screenMidPoint - 100.0f;
    path->AddCurve({ Vector2(-40.0f, 720.0f), Vector2(-50.0f , 720.0f), Vector2(10.0f, 720.0f), Vector2(0.0f, 720.0f) }, 1);
    path->AddCurve({ Vector2(0.0f, 720.0f), Vector2(200.0f, 720.0f), Vector2(temp, 500.0f), Vector2(temp, 400.0f) }, 15);
    path->AddCurve({ Vector2(temp, 400.0f), Vector2(temp, 200.0f), Vector2(40.0f, 200.0f), Vector2(40.0f, 400.0f) }, 15);
    path->AddCurve({ Vector2(40, 400.0f), Vector2(40, 500.0f), Vector2(temp - 120.0f, 600.0f), Vector2(temp - 40.0f, 440.0f) }, 15);

    sPaths.push_back(std::vector<Vector2>());
    path->Sample(&sPaths[currentPath]);
    delete path;
    
    currentPath = 3;
    path = new BezierPath();
    temp = screenMidPoint + 60.0f;
    int temp2 = fullScreen - 40.0f;
    path->AddCurve({ Vector2(temp2 + 40.0f, 720.0f), Vector2(temp2 + 50.0f , 720.0f), Vector2(temp2 + 10.0f, 720.0f), Vector2(temp2, 720.0f) }, 1);
    path->AddCurve({ Vector2(temp2, 720.0f), Vector2(temp2 - 200.0f, 720.0f), Vector2(temp, 500.0f), Vector2(temp, 400.0f) }, 15);
    path->AddCurve({ Vector2(temp, 400.0f), Vector2(temp, 200.0f), Vector2(temp2 - 40.0f, 200.0f), Vector2(temp2 - 40.0f, 400.0f) }, 15);
    path->AddCurve({ Vector2(temp2 - 40, 400.0f), Vector2(temp2 - 40, 500.0f), Vector2(temp + 120.0f, 600.0f), Vector2(temp + 40.0f, 440.0f) }, 15);

    sPaths.push_back(std::vector<Vector2>());
    path->Sample(&sPaths[currentPath]);
    delete path;


}

void Enemy::SetFormation(Formation* f)
{
    sFormation = f;
}

void Enemy::CurrentPlayer(Player* player)
{
    sPlayer = player;
}

Enemy::Enemy(int index, int path, bool challengeStage)
{
    mTimer = Timer::Instance();

    //bezier path initialization
    mCurrentPath = path;

    mCurrentState = flyin;

    mCurrentWaypoint = 1;
    Pos(sPaths[mCurrentPath][0]);

    //The two textures used for animating the enemies
    mTextures[0] = NULL;
    mTextures[1] = NULL;

    mSpeed = 400.0f;

    mIndex = index;

    mChallengeStage = challengeStage;

    //collider id
    mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

    //death animation texture load
    mDeathAnimation = new AnimatedTexture("enemyExp.png", 0, 0, 128,128, 5, 1.0f, AnimatedTexture::horizontal);
    mDeathAnimation->Parent(this);
    mDeathAnimation->Pos(VEC2_ZERO);
    mDeathAnimation->WrapMode(AnimatedTexture::once);
}

Enemy::~Enemy()
{
    mTimer = NULL;

    delete mTextures[0];
    delete mTextures[1];
    mTextures[0] = NULL;
    mTextures[1] = NULL;

    delete mDeathAnimation;
    mDeathAnimation = nullptr;
}


void Enemy::Hit(PhysicsEntity* other)
{
    //kill object when hit
    if (mCurrentState == formation)
    {
        Parent(nullptr);
    }

    mCurrentState = dead;
}

void Enemy::PathComplete()
{
    //no formation in challenge stages
    if (mChallengeStage)
    {
        mCurrentState = dead;
    }
}

void Enemy::JoinFormation()
{
    Pos(WorldFormationPosition());
    Parent(sFormation);
    mCurrentState = formation;
}

Vector2 Enemy::WorldFormationPosition()
{
    return sFormation->Pos() + LocalFormationPosition();
}

void Enemy::FlyInComplete()
{
    if (mChallengeStage)
    {
        mCurrentState = dead;
    }
    else
    {
        JoinFormation();
    }
}

void Enemy::HandleFlyInState()
{
    if (mCurrentWaypoint < sPaths[mCurrentPath].size())
    {
        Vector2 dist = sPaths[mCurrentPath][mCurrentWaypoint] - Pos();
        Translate(dist.Normalized() * mTimer->DeltaTime() * mSpeed, world);

        Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

        if ((sPaths[mCurrentPath][mCurrentWaypoint] - Pos()).MagnitudeSqr() < EPSILON)
        {
            mCurrentWaypoint++;
        }

        if (mCurrentWaypoint >= sPaths[mCurrentPath].size())
        {
            PathComplete();
        }
    }
    else
    {
        Vector2 dist = WorldFormationPosition() - Pos();
        Translate(dist.Normalized() * mTimer->DeltaTime() * mSpeed, world);

        Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

        if (dist.MagnitudeSqr() < EPSILON)
        {
            FlyInComplete();
        }
    }
}

void Enemy::HandleFormationState()
{
    Pos(LocalFormationPosition());

    float rotation = Rotation();
    //when in formation rotate facing down
    if (rotation != 0)
    {
        if (rotation > 2.0f)
        {
            float rotationSpeed = 200.0f;
            float rotationDir = (rotation == 180.0f) ? 1.0f : rotation - 180.0f;
            Rotate((rotationDir / abs(rotationDir)) * mTimer->DeltaTime() * rotationSpeed);
        }
        else
        {
            Rotation(0);
        }
    }
}

void Enemy::HandleDeadState()
{
    if (mDeathAnimation->IsAnimating())
    {
        mDeathAnimation->Update();
    }
}

void Enemy::HandleStates()
{
    switch (mCurrentState)
    {
    case flyin:

        HandleFlyInState();
        break;

    case formation:

        HandleFormationState();
        break;

    case dive:

        HandleDiveState();
        break;

    case dead:

        HandleDeadState();
        break;
    }
}

void Enemy::RenderFlyInState()
{
    mTextures[0]->Render();
}

void Enemy::RenderFormationState()
{
    mTextures[sFormation->GetTick() % 2]->Render();
}

void Enemy::RenderDeadState()
{
    if (mDeathAnimation->IsAnimating())
    {
        mDeathAnimation->Render();
    }
}

void Enemy::RenderStates()
{
    switch (mCurrentState)
    {
    case flyin:

        RenderFlyInState();
        break;

    case formation:

        RenderFormationState();
        break;

    case dive:

        RenderDiveState();
        break;

    case dead:

        RenderDeadState();
        break;
    }

    PhysicsEntity::Render();
}

bool Enemy::IgnoreCollisions()
{
    return mCurrentState == dead;
}

Enemy::STATES Enemy::CurrentState()
{
    return mCurrentState;
}

Enemy::TYPES Enemy::Type()
{
    return mType;
}

int Enemy::Index()
{
    return mIndex;
}

void Enemy::Dive(int type)
{
    Parent(NULL);
    mCurrentState = dive;
    mDiveStartPosition = Pos();
    mCurrentWaypoint = 1;
}

bool Enemy::InDeathAnimation()
{
    return mDeathAnimation->IsAnimating();
}

void Enemy::Update()
{
    if (Active())
    {
        HandleStates();
    }
}

void Enemy::Render()
{
    if (Active())
    {
        RenderStates();
        /*for (int i = 0; i < sPaths[mCurrentPath].size() - 1; ++i)
        {
            Graphics::Instance()->DrawLine(sPaths[mCurrentPath][i].x, sPaths[mCurrentPath][i].y, sPaths[mCurrentPath][i + 1].x, sPaths[mCurrentPath][i + 1].y);
        }*/
    }
}