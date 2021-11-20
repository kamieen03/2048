#include "Game.hpp"

Game::Game()
{
    srand(time(NULL));
}

int Game::run()
{
    while(true)
    {
        // player loses the game
        if(!renderElement())
        {
            showLoseScreen();
            break;
        }
        
        // player enters key (might want to quit)
        auto key = keyHandler();
        if(key == keyHandler::QUIT_KEY)
        {
            break;
        }
        
        // game engine updates the board
        updateGrid(key);

        // player wins (either continues playing or quits)
        if(!achieved2048 && grid.has2048())
        {
            achieved2048 = true;
            const auto winDecision = showWinScreen();
            if(winDecision == WinDecision::QUIT)
                break;
        }

        showBoard();
    }
    return score;
}

bool Game::renderElement()
{
    if(grid.isFull())
    {
        return false;
    }
    else
    {
        const auto freeTiles = grid.getFreeTiles();
        const auto N = freeTiles.size();
        const auto randomFreeTile = freeTiles[rand() % N];
        const auto newNumber = rand() % 4 <= 1 ? 2 : 4;
        grid.setTile(randomFreeTile, number);
        return true;
    }
}

void showBoard()
{
    cv::imshow("2048", grid.getImage()); 
}

void updateGrid(KeyHandler::Key key)
{

}

void Game::showLoseScreen()
{

}

Game::WinDecision Game::showWinScreen()
{
    return Game::WinDecision::QUIT;
}
