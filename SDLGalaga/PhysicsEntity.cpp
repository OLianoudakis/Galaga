#include "PhysicsEntity.h"
#include "PhysicsHelper.h"
#include "PhysicsManager.h"

PhysicsEntity::PhysicsEntity()
{
    mBroadPhaseCollider = nullptr;
    mId = 0;
}

PhysicsEntity::~PhysicsEntity()
{
    for (int i = 0; i < mColliders.size(); ++i)
    {
        delete mColliders[i];
        mColliders[i] = nullptr;
    }

    mColliders.clear();

    if (mBroadPhaseCollider)
    {
        delete mBroadPhaseCollider;
        mBroadPhaseCollider = nullptr;
    }

    if (mId != 0)
    {
        PhysicsManager::Instance()->UnregisteredEntity(mId);
    }
}

unsigned long PhysicsEntity::GetId()
{
    return mId;
}

bool PhysicsEntity::CheckCollision(PhysicsEntity* other)
{
    //Ignore is called if layers that would collide now shouldn't
    if (IgnoreCollisions() || other->IgnoreCollisions())
    {
        return false;
    }

    //check collision 
    return ColliderColliderCheck(mBroadPhaseCollider, other->mBroadPhaseCollider);
}

void PhysicsEntity::Hit(PhysicsEntity* other)
{

}

bool PhysicsEntity::IgnoreCollisions()
{
    return false;
}

void PhysicsEntity::AddCollider(Collider* collider, Vector2 localPos)
{
    //add collider to the object and list
    collider->Parent(this);
    collider->Pos(localPos);
    mColliders.push_back(collider);

    //Create circle collider out of the individual box colliders while calculating furthest distance
    if (mColliders.size() > 1 || mColliders[0]->GetType() != Collider::ColliderType::Circle)
    {
        float furthestDistance = mColliders[0]->GetFurthestPoint().Magnitude();
        float dist = 0.0f;
        for (int i = 1; i < mColliders.size(); ++i)
        {
            dist = mColliders[i]->GetFurthestPoint().Magnitude();
            if (dist > furthestDistance)
            {
                furthestDistance = dist;
            }
        }

        //add circle collider as the broadphasecollider
        delete mBroadPhaseCollider;
        mBroadPhaseCollider = new CircleCollider(furthestDistance, true);
        mBroadPhaseCollider->Parent(this);
        mBroadPhaseCollider->Pos(VEC2_ZERO);
    }
}

void PhysicsEntity::Render()
{
    for (int i = 0; i < mColliders.size(); ++i)
    {
        mColliders[i]->Render();
    }
}