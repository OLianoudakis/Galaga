#ifndef _BULLET_H
#define _BULLET_H
#include "PhysicsEntity.h"
#include "Timer.h"

class Bullet : public PhysicsEntity
{
private:

    const int OFFSCREEN_BUFFER = 10;

    Timer* mTimer;

    float mSpeed;

    Texture* mTexture;

public:

    Bullet(bool friendly);
    ~Bullet();

    void Fire(Vector2 pos);
    void Reload();

    void Hit(PhysicsEntity* other) override;

    void Update();

    void Render();

private:

    bool IgnoreCollisions() override;
};
#endif // !_BULLET_H

