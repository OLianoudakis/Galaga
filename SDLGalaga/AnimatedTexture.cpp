#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir)
    : Texture(filename, x, y, w, h)
{
    mTimer = Timer::Instance();

    mStartX = x;
    mStartY = y;

    mFrameCount = frameCount;
    mAnimationSpeed = animationSpeed;
    mTimePerFrame = mAnimationSpeed / mFrameCount;
    mAnimationTimer = 0.0f;

    mAnimationDirection = animationDir;

    mAnimationDone = false;

    mWrapMode = loop;
    //default settings
}

AnimatedTexture::~AnimatedTexture()
{

}
//new method
void AnimatedTexture::RunAnimation()
{
    mAnimationTimer += mTimer->DeltaTime();

    if (mAnimationTimer >= mAnimationSpeed)
    {
        if (mWrapMode == loop)
        {
            mAnimationTimer -= mAnimationSpeed;
        }
        else
        {
            mAnimationDone = true;
            mAnimationTimer = mAnimationSpeed - mTimePerFrame;
        }
    }

    if (mAnimationDirection == horizontal)
    {
        mClipRect.x = mStartX + (int)(mAnimationTimer / mTimePerFrame) * mWidth;
    }
    else
    {
        mClipRect.y = mStartY + (int)(mAnimationTimer / mTimePerFrame) * mHeight;
    }
}

void AnimatedTexture::WrapMode(WRAP_MODE mode)
{
    mWrapMode = mode;
}
//new method
void AnimatedTexture::ResetAnimation()
{
    mAnimationTimer = 0.0f;
    mAnimationDone = false;
}
//new method
bool AnimatedTexture::IsAnimating()
{
    return !mAnimationDone;
}
//altered method
void AnimatedTexture::Update()
{
    if (!mAnimationDone)
    {
        RunAnimation();
    }
}