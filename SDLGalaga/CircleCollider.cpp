#include"CircleCollider.h"

//circle collider init
CircleCollider::CircleCollider(float radius, bool broadphase)
    :Collider(ColliderType::Circle)
{
    mRadius = radius;

    if (DEBUG_COLLIDERS)
    {
        if (broadphase)
        {
            SetDebugTexture(new Texture("BroadPhaseCollider.png"));
        }
        else
        {
            SetDebugTexture(new Texture("CircleCollider.png"));
        }

        mDebugTexture->Scale(VEC2_ONE * (radius * 2 / 100.0f));
    }
}

CircleCollider::~CircleCollider()
{

}

//get furthest point from circle collider
Vector2 CircleCollider::GetFurthestPoint()
{
    return VEC2_RIGHT * (mRadius + Pos(GameEntity::local).Magnitude());
}

float CircleCollider::GetRadius()
{
    return mRadius;
}