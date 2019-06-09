#ifndef _PHYSICSENTITY_H
#define _PHYSICSENTITY_H

#include<vector>

#include"Collider.h"

class PhysicsEntity : public GameEntity
{
protected:
    //ID of object
    unsigned long mId;

    //List of Colliders in the object
    std::vector<Collider*> mColliders;

    //Type of Collider
    Collider* mBroadPhaseCollider;

public:
    //constructor - destructor
    PhysicsEntity();
    ~PhysicsEntity();

    unsigned long GetId();

    bool CheckCollision(PhysicsEntity* other);

    virtual void Hit(PhysicsEntity* other);

    //render colliders (used for debugging)
    virtual void Render();

protected:

    virtual bool IgnoreCollisions();

    void AddCollider(Collider* collider, Vector2 localPos = VEC2_ZERO);
};
#endif // !_PHYSICSENTITY_H

