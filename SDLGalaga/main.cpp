#include "GameManager.h"

int main(int arc, char* argv[])
{
    //Instance game manager
    GameManager* game = GameManager::Instance();

    //run game
    game->Run();
    
    //release game manager data
    GameManager::Release();
    game = NULL;

    return 0;
}