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
        if(!grid.isFull() and changed)
        {
            renderElement();
        }
        showBoard();

        // player loses the game
        if(grid.isFull() and !grid.canMove())
        {
            showLoseScreen();
            break;
        }

        // player enters key (might want to quit)
        auto key = KeyHandler::get().handle();
        if(key == KeyHandler::Key::QUIT)
        {
            const auto decision = showMenu();
            if(decision == CQDecision::QUIT)
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
            if(winDecision == CQDecision::QUIT)
                break;
        }

    }
    return score;
}

void Game::renderElement()
{
    const auto freeTiles = grid.getFreeTiles();
    const auto N = freeTiles.size();
    const auto randomFreeTile = freeTiles[rand() % N];
    const auto newNumber = rand() % 4 <= 1 ? 2 : 4;
    grid.setTile(*randomFreeTile, newNumber);
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
    image = grid.getImage();
    pastePopUpScreen(LoseScreen::get().getImage());
    cv::imshow("2048", image);
    return handleLoseScreenKeys();
}

CQDecision Game::showWinScreen()
{
    image = grid.getImage();
    pastePopUpScreen(WinScreen::get().getImage());
    cv::imshow("2048", image);
    return handleWinScreenKeys();
}

void Game::pastePopUpScreen(const cv::Mat& popUpScreen)
{
    graphics::pasteRectangleOntoImageCentered(popUpScreen, image);
}

CQDecision Game::handleWinScreenKeys()
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
        }
        else if(key == KeyHandler::Key::RIGHT)
        {
            WinScreen::get().setRightOption();
        }
        pastePopUpScreen(WinScreen::get().getImage());
        cv::imshow("2048", image);
    }
}

void Game::handleLoseScreenKeys()
{
    int key {0};
    while(key = cv::waitKey() & 0xFF)
    {
        if(key == KeyHandler::Key::ENTER or key == KeyHandler::Key::QUIT)
        {
            return;
        }
    }
}

void Game::updateColorScheme(const ColorScheme& cs)
{
    grid.updateColorScheme(cs);
}

CQDecision Game::showMenu()
{
    image = grid.getImage();
    pastePopUpScreen(menu.getImage());
    cv::imshow("2048", image);
    return handleMenuKeys();
}

CQDecision Game::handleMenuKeys()
{
    Key key;
    while(key = Key(cv::waitKey() & 0xFF))
    {
        const auto menuSignalSet = menu.handleKey(key);
        if(menuSignalSet.changedColorScheme)
        {
            updateColorScheme(menu.getActiveScheme());
            image = grid.getImage();
        }
        else if(menuSignalSet.cqDecision)
        {
            return *menuSignalSet.cqDecision;
        }
        pastePopUpScreen(menu.getImage());
        cv::imshow("2048", image);
    }
}
