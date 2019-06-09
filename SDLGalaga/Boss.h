#ifndef _BOSS_H
#define _BOSS_H
#include "Enemy.h"
#include "CaptureBeam.h"

class Boss : public Enemy
{

private:

    static std::vector<std::vector<Vector2>> sDivePaths;

    bool mCaptureDive;

    int mCurrentPath;

    bool mCapturing;

    CaptureBeam* mCaptureBeam;

    bool mWasHit;

private:

    Vector2 LocalFormationPosition();

    void HandleCaptureBeam();

    void HandleDiveState() override;

    void RenderDiveState() override;

public:

    static void CreateDivePaths();

    Boss(int index, int path, bool challengeStage);
    ~Boss();

    void Dive(int type = 0);

    void Hit(PhysicsEntity* other) override;
};

#endif // !_BOSS_H

