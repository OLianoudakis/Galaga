#include "Bullet.h"
#include"BoxCollider.h"
#include"PhysicsManager.h"

//constructor
Bullet::Bullet(bool friendly)
{
    mTimer = Timer::Instance();

    mSpeed = 1000.0f;

    mTexture = new Texture("bullet.png");
    mTexture->Parent(this);
    mTexture->Pos(VEC2_ZERO);

    Reload();

    AddCollider(new BoxCollider(mTexture->ScaledDimentions()));

    //register collision layer depeding who calls the method
    if (friendly)
    {
        PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::FriendlyProjectiles);
    }
    else
    {
        PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::HostileProjecttiles);
    }
}

Bullet::~Bullet()
{
    mTimer = NULL;

    delete mTexture;
    mTexture = NULL;
}

void Bullet::Fire(Vector2 pos)
{
    Pos(pos);
    Active(true);
}

//disable until less than 2 bullets are active
void Bullet::Reload()
{
    Active(false);
}

void Bullet::Hit(PhysicsEntity* other)
{
    Reload();
}

bool Bullet::IgnoreCollisions()
{
    return !Active();
}

void Bullet::Update()
{
    //move object
    if (Active())
    {
        Translate(-VEC2_UP * mSpeed * mTimer->DeltaTime(), local);

        Vector2 pos = Pos();

        //despawn after exiting screen
        if (pos.y < -OFFSCREEN_BUFFER || pos.y > Graphics::Instance()->SCREEN_HEIGHT + OFFSCREEN_BUFFER)
        {
            Reload();
        }
    }
}

void Bullet::Render()
{
    if (Active())
    {
        mTexture->Render();
        PhysicsEntity::Render();
    }
}