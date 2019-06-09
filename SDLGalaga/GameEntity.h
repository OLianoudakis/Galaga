#ifndef _GAMEENTITY_H
#define _GAMEENTITY_H
#include "MathHelper.h"

//base class for every entity created
class GameEntity
{
public:

    //define space
    enum SPACE { local = 0, world = 1 };

private:

    //transform attributes
    Vector2 mPos;
    float mRotation;
    Vector2 mScale;

    bool mActive; //store activity of object
    GameEntity* mParent; //link objects together with parent-child system

public:
    //constructor - destructor
    GameEntity(float x = 0.0f, float y = 0.0f);
    ~GameEntity();

    void Pos(Vector2 pos);
    Vector2 Pos(SPACE space = world);

    void Rotation(float rotation);
    float Rotation(SPACE space = world);

    void Scale(Vector2 scale);
    Vector2 Scale(SPACE space = world);

    void Active(bool active);
    bool Active();

    void Parent(GameEntity* parent);
    GameEntity* Parent();

    void Translate(Vector2 vec, SPACE space = local);
    void Rotate(float amount);

    virtual void Update();
    virtual void Render();
};

#endif // !_GAMEENTITY_H

