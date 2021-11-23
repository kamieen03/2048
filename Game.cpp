#include "Game.hpp"
#include <iostream>
#define LOG(X) std::cout << X << std::endl;

Game::Game()
{
    srand(time(NULL));
    cv::namedWindow("2048", CV_WINDOW_AUTOSIZE);
}

int Game::run()
{
    showBoard();
    bool changed = true;
    while(true)
    {
        // player loses the game
        if(changed and !renderElement())    // using lazy evaluation
        {
            showLoseScreen();
            break;
        }
        showBoard();
        
        // player enters key (might want to quit)
        auto key = keyHandler();
        if(key == KeyHandler::Key::QUIT)
        {
            break;
        }
        
        // game engine updates the board
        changed = updateGrid(key);
        showBoard();

        // player wins (either continues playing or quits)
        if(!achieved2048 && grid.has2048())
        {
            achieved2048 = true;
            const auto winDecision = showWinScreen();
            if(winDecision == WinScreen::WinDecision::QUIT)
                break;
        }

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
        const auto freeTiles = grid.getFreeTilesCoordinates();
        const auto N = freeTiles.size();
        const auto randomFreeTile = freeTiles[rand() % N];
        const auto newNumber = rand() % 4 <= 1 ? 2 : 4;
        grid.setTile(randomFreeTile, newNumber);
        return true;
    }
}

void Game::showBoard()
{
    image = grid.getImage();
    cv::imshow("2048", image); 
}

bool Game::updateGrid(KeyHandler::Key key)
{
    return grid.update(key);
}

void Game::showLoseScreen()
{
    //TODO
}

WinScreen::WinDecision Game::showWinScreen()
{
    image = grid.getImage();
    pasteWinScreen();
    cv::imshow("2048", image);
    return handleWinScreenKeys();
}

void Game::pasteWinScreen()
{
    const auto w = (image.cols - WinScreen::WIDTH)  / 2;
    const auto h = (image.rows - WinScreen::HEIGHT) / 2;
    auto dst = image(cv::Rect(w, h, WinScreen::WIDTH, WinScreen::HEIGHT));
    WinScreen::get().getImage().copyTo(dst);
}

WinScreen::WinDecision Game::handleWinScreenKeys()
{
    int key {0};
    while(key = cv::waitKey() & 0xFF)
    {
        if(key == KeyHandler::Key::ENTER)
        {
            return WinScreen::get().getWinDecision();
        }
        else if(key == KeyHandler::Key::LEFT)
        {
            WinScreen::get().setLeftOption();
            pasteWinScreen();
            cv::imshow("2048", image);
        }
        else if(key == KeyHandler::Key::RIGHT)
        {
            WinScreen::get().setRightOption();
            pasteWinScreen();
            cv::imshow("2048", image);
        }
    }
}
