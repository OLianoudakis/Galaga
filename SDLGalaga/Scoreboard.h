#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H
#include"Texture.h"
#include<vector>

class Scoreboard : public GameEntity
{

private:

    std::vector<Texture*> mScore;
    int mScoreInt;

    SDL_Color mColor;

public:

    Scoreboard();
    Scoreboard(SDL_Color color);
    ~Scoreboard();

    void Score(int score);
    int GetScore();

    void Render();

private:

    void ClearBoard();
};

#endif // !_SCOREBOARD_H

