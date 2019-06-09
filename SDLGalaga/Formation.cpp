#include "Formation.h"

Formation::Formation()
{
    mTimer = Timer::Instance();

    //Movement Timers
    mOffsetAmount = 10.0f;
    mOffsetDelay = 0.4f;
    mOffsetTimer = 0.0f;
    mOffsetCounter = 4;
    mOffsetDirection = 1;

    //Breathing Spread vars
    mSpreadTimer = 0.0f;
    mSpreadDelay = 0.6f;
    mSpreadCounter = 0;
    mSpreadDirection = 1;

    mLocked = false; //after all ships land in position this is true

    mGridSize = Vector2(32.0, 64.0f);
}

Formation::~Formation()
{
    mTimer = NULL;
}

Vector2 Formation::GridSize()
{
    return mGridSize;
}

int Formation::GetTick()
{
    if (!mLocked || mOffsetCounter != 4)
    {
        return mOffsetCounter;
    }
    else
    {
        return mSpreadCounter;
    }
}

void Formation::Lock()
{
    mLocked = true;
}

bool Formation::Locked()
{
    return mLocked && mOffsetCounter == 4;
}

//Move the Grid
void Formation::Update()
{
    //when not locked
    if (!mLocked || mOffsetCounter != 4)
    {
        mOffsetTimer += mTimer->DeltaTime();
        if (mOffsetTimer >= mOffsetDelay)
        {
            mOffsetCounter++;
            Translate(VEC2_RIGHT * mOffsetDirection * mOffsetAmount, world);

            if (mOffsetCounter == 8)
            {
                mOffsetCounter = 0;
                mOffsetDirection *= -1;
            }

            mOffsetTimer = 0.0f;
        }
    }
    else
    {//after lock breathing animation takes place
        mSpreadTimer += mTimer->DeltaTime();
        if (mSpreadTimer >= mSpreadDelay)
        {
            mSpreadCounter += mSpreadDirection;

            mGridSize.x += (mSpreadDirection * ((mSpreadCounter % 2 == 0) ? 1 : 2));

            if (mSpreadCounter == 4 || mSpreadCounter == 0)
            {
                mSpreadDirection *= -1;
            }

            mSpreadTimer = 0.0f;
        }
    }
}