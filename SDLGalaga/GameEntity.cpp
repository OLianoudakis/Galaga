#include "GameEntity.h"
//constructor
//slightly altered method
GameEntity::GameEntity(float x, float y)
{
    mPos.x = x;
    mPos.y = y;

    mRotation = 0.0f;

    mActive = true;

    mParent = NULL;

    mScale = VEC2_ONE;
}
//destructor
GameEntity::~GameEntity()
{
    mParent = NULL;
}
//Set position
void GameEntity::Pos(Vector2 pos)
{
    mPos = pos;
}
//get position either world or local
Vector2 GameEntity::Pos(SPACE space)
{
    if (space == local || mParent == NULL)
    {
        return mPos;
    }

    Vector2 parentScale = mParent->Scale(world);
    Vector2 rotPos = RotateVector(Vector2(mPos.x * parentScale.x, mPos.y * parentScale.y), mParent->Rotation(local));

    //rotate child depending on parent and its scale
    return mParent->Pos(world) + rotPos;
}
//set entity rotation from 0 to 360
void GameEntity::Rotation(float r)
{
    mRotation = r;

    if (mRotation > 360.0f) 
    {
        int mul = mRotation / 360;
        mRotation -= 360.0f * mul;
    }
    else if (mRotation < 0.0f) 
    {
        int mul = (mRotation / 360) - 1;
        mRotation -= 360.0f * mul;
    }
}

float GameEntity::Rotation(SPACE space)
{
    if (space == local || mParent == NULL)
    {
        return mRotation;
    }

    return mParent->Rotation(world) + mRotation;
}
//Set scale
void GameEntity::Scale(Vector2 scale)
{
    mScale = scale;
}
//get scale
Vector2 GameEntity::Scale(SPACE space)
{
    if (space == local || mParent == NULL)
    {
        return mScale;
    }

    Vector2 scale = mParent->Scale(world);
    scale.x *= mScale.x;
    scale.y *= mScale.y;

    return scale;
}
//set activity
void GameEntity::Active(bool active)
{
    mActive = active;
}
//get activity
bool GameEntity::Active()
{
    return mActive;
}
//Set Parent
void GameEntity::Parent(GameEntity* parent)
{
    //set new local pos
    if (parent == NULL)
    {
        mPos = Pos(world);
        mRotation = Rotation(world);
        mScale = Scale(world);
    }
    else
    {
        if (mParent != NULL)
        {
            Parent(NULL);
        }
        //Set transform attributes in corrolation to parent object
        Vector2 parentScale = parent->Scale(world);

        mPos = RotateVector(Pos(world) - parent->Pos(world), -parent->Rotation(world));
        mPos.x /= parentScale.x;
        mPos.y /= parentScale.y;

        mRotation -= parent->Rotation(world);

        mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
    }

    mParent = parent;
}
//get parent object
GameEntity* GameEntity::Parent()
{
    return mParent;
}
//translate object to position
//altered method taking into consideration space
void GameEntity::Translate(Vector2 vec, SPACE space)
{
    if (space == world)
    {
        mPos += vec;
    }
    else
    {
        mPos += RotateVector(vec, Rotation());
    }
}
//rotate object
void GameEntity::Rotate(float amount)
{
    Rotation(mRotation + amount);
}

void GameEntity::Update()
{

}

void GameEntity::Render()
{

}