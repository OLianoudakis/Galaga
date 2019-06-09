#ifndef _BACKGROUNDSTARS_H
#define _BACKGROUNDSTARS_H
#include"StarLayer.h"

class BackgroundStars
{
    static BackgroundStars* sInstance;

    // 3 different layers of stars
    static const int LAYER_COUNT = 3;
    StarLayer* mLayers[LAYER_COUNT];

public:

    static BackgroundStars* Instance();
    static void Release();

    //decide if scorlling stars or stationary
    void Scroll(bool b);

    void Update();
    void Render();

private:

    BackgroundStars();
    ~BackgroundStars();
};

#endif // !_BACKGROUNDSTARS_H

