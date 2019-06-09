#ifndef _ENEMY_H
#define _ENEMY_H
#include "AnimatedTexture.h"
#include "BezierPath.h"
#include "Formation.h"
#include "PhysicsEntity.h"
#include "Player.h"

class Enemy : public PhysicsEntity
{

public:

    enum STATES { flyin, formation, dive, dead };
    enum TYPES { butterfly, wasp, boss };

protected:

    static std::vector<std::vector<Vector2>> sPaths;
    static Formation* sFormation;    
    static Player* sPlayer;

    Timer* mTimer;

    Texture* mTextures[2];

    STATES mCurrentState;

    int mCurrentPath;

    int mCurrentWaypoint;
    const float EPSILON = 50.0f; //how far we want to be from a waypoint to go to the next one

    float mSpeed;

    TYPES mType;
    int mIndex;

    bool mChallengeStage;

    Vector2 mDiveStartPosition;

    AnimatedTexture* mDeathAnimation;

protected:
    
    virtual void PathComplete();

 
    virtual void FlyInComplete();

    void JoinFormation();
    virtual Vector2 WorldFormationPosition();
    //Pure Virtual because this class cannot know initially the type of enemy
    virtual Vector2 LocalFormationPosition() = 0;

    virtual void HandleFlyInState();
    virtual void HandleFormationState();
    //different dive animation types and death
    virtual void HandleDiveState() = 0;
    virtual void HandleDeadState();

    void HandleStates();

    virtual void RenderFlyInState();
    virtual void RenderFormationState();
    virtual void RenderDiveState() = 0;
    virtual void RenderDeadState();

    void RenderStates();

    bool IgnoreCollisions() override;

public:

    static void CreatePaths();
    static void SetFormation(Formation* f);
    static void CurrentPlayer(Player* player);

    Enemy(int index, int path, bool challengeStage);
    virtual ~Enemy();

    virtual void Hit(PhysicsEntity* other) override;

    STATES CurrentState();

    TYPES Type();
    int Index();

    virtual void Dive(int type = 0);

    bool InDeathAnimation();

    void Update();

    void Render();
};

#endif // !_ENEMY_H

