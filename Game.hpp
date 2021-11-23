#include <stdlib.h>
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Grid.hpp"
#include "Screen.hpp"
#include "KeyHandler.hpp"

class Game
{
public:
    Game();
    int run();

private:

    bool renderElement();
    void showBoard();
    bool updateGrid(KeyHandler::Key);
    void showLoseScreen();
    WinScreen::WinDecision showWinScreen();
    void pasteWinScreen();
    WinScreen::WinDecision handleWinScreenKeys();

    cv::Mat image {Grid::IMAGE_SIZE, Grid::IMAGE_SIZE, CV_8UC3,CV_RGB(0,0,0)};
    bool achieved2048 {false};
    int score {0};
    Grid grid {};
    KeyHandler keyHandler {};
};

