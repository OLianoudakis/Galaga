#include "CaptureBeam.h"

//animate beam horizontaly but introduce a sizable clipping here to simulate the spread animation

CaptureBeam::CaptureBeam()
    : AnimatedTexture("captureBeam.png", 0, 0, 184, 320, 3, 0.5f, horizontal)
{
    mTotalCaptureTime = 6.0f;
    ResetAnimation();
}

CaptureBeam::~CaptureBeam()
{

}

void CaptureBeam::ResetAnimation()
{
    AnimatedTexture::ResetAnimation();
    mCaptureTimer = 0.0f;
    mClipRect.h = 0;
}

//change clipping height to simulate the spread of the beam
//remove (int) casts for smooth animation. keep them for retro style
void CaptureBeam::RunAnimation()
{
    mCaptureTimer += mTimer->DeltaTime();
    if (mCaptureTimer >= mTotalCaptureTime)
    {
        mAnimationDone = true;
    }
    else
    {
        mAnimationTimer += mTimer->DeltaTime();

        if (mAnimationTimer >= mAnimationSpeed)
        {
            mAnimationTimer -= mAnimationSpeed;
        }

        mClipRect.x = (int)(mAnimationTimer / mTimePerFrame) * mWidth;

        if (mCaptureTimer < 2.0f)
        {
            float temp = (int)(mCaptureTimer * 3.5f);
            mClipRect.h = (int)((temp / 7.0f) * mHeight);
        }
        else if (mCaptureTimer > mTotalCaptureTime - 2.0f)
        {
            float temp = (int)((mTotalCaptureTime - mCaptureTimer) * 3.5f);
            mClipRect.h = (int)((temp / 7.0f) * mHeight);
        }
        else
        {
            mClipRect.h = mHeight;
        }
    }
}

//render beam
void CaptureBeam::Render()
{
    Vector2 pos = Pos(world);
    Vector2 scale = Scale(world);

    //according to clip
    mRenderRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
    mRenderRect.y = (int)(pos.y - mHeight * scale.y * 0.5f);
    mRenderRect.w = (int)(mWidth * scale.x);
    mRenderRect.h = mClipRect.h;

    mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(world));
}