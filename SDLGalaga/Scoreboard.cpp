#include "Scoreboard.h"

Scoreboard::Scoreboard()
    : Scoreboard({230, 230, 230})
{
    mScoreInt = 0;
}

Scoreboard::Scoreboard(SDL_Color color)
{
    mColor = color;
    Score(0);
}

Scoreboard::~Scoreboard()
{
    ClearBoard();
}

void Scoreboard::ClearBoard()
{
    for (int i = 0; i < mScore.size(); ++i)
    {
        delete mScore[i];
        mScore[i] = NULL;
    }

    mScore.clear();
}

//calculate score
void Scoreboard::Score(int score)
{
    ClearBoard();

    mScoreInt = score;

    if (score == 0)
    {
        for (int i = 0; i < 2; ++i)
        {
            mScore.push_back(new Texture("0", "emulogic.ttf", 32, mColor));
            mScore[i]->Parent(this);
            mScore[i]->Pos(Vector2(-32.0f * i, 0.0f));
        }
    }
    else
    {
        //make int to string
        std::string str = std::to_string(score);
        int lastIndex = str.length() - 1;

        for (int i = 0; i <= lastIndex; ++i)
        {
            mScore.push_back(new Texture(str.substr(i, 1), "emulogic.ttf", 32, mColor));
            mScore[i]->Parent(this);
            mScore[i]->Pos(Vector2(-32.0f * (lastIndex - i), 0.0f));
        }
    }
}

int Scoreboard::GetScore()
{
    return mScoreInt;
}

void Scoreboard::Render()
{
    for (int i = 0; i < mScore.size(); ++i)
    {
        mScore[i]->Render();
    }
}