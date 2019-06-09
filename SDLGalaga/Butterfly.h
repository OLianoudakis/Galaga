#ifndef _BUTTERFLY_H
#define _BUTTERFLY_H
#include "Enemy.h"

class Butterfly : public Enemy
{

private:

    static std::vector<std::vector<Vector2>> sDivePaths;

    bool mEscort;

private:

    Vector2 LocalFormationPosition();

    void HandleDiveState() override;

    void RenderDiveState() override;

public:

    static void CreateDivePaths();

    Butterfly(int index, int path, bool challengeStage);
    ~Butterfly();

    void Dive(int type = 0);

    void Hit(PhysicsEntity* other) override;
};

#endif // !_BUTTERFLY_H

