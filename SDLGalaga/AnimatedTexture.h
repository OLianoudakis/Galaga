#ifndef _ANIMATEDTEXTURE_H
#define _ANIMATEDTEXTURE_H
#include "Timer.h"
#include "Texture.h"
#include <iostream>

using namespace std;

class AnimatedTexture : public Texture
{
public:

    enum WRAP_MODE { once = 0, loop = 1 };
    enum ANIM_DIR { horizontal = 0, vertical = 1 };

protected:

    Timer* mTimer;
    //initial position for clipping in the texture
    int mStartX;
    int mStartY;

    //variables for speed calculation
    float mAnimationTimer;
    float mAnimationSpeed;
    float mTimePerFrame;

    //number of frames in the sprite animation
    int mFrameCount;

    WRAP_MODE mWrapMode;
    ANIM_DIR mAnimationDirection;

    bool mAnimationDone;

protected:

    virtual void RunAnimation();

public:

    AnimatedTexture(string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir);
    ~AnimatedTexture();

    void WrapMode(WRAP_MODE mode);

    virtual void ResetAnimation();

    bool IsAnimating();

    void Update();
};
#endif // !_ANIMATEDTEXTURE_H

