#include <stdlib.h>
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Grid.hpp"
#include "InfoScreen.hpp"
#include "KeyHandler.hpp"

class Game
{
public:
    Game();
    int run();

private:
    void renderElement();
    void showBoard();
    bool updateGrid(KeyHandler::Key);
    WinScreen::WinDecision showWinScreen();
    void showLoseScreen();
    void pasteInfoScreen(InfoScreen& s);
    WinScreen::WinDecision handleWinScreenKeys();
    void handleLoseScreenKeys();

    cv::Mat image {Grid::IMAGE_SIZE, Grid::IMAGE_SIZE, CV_8UC3,CV_RGB(0,0,0)};
    bool achieved2048 {false};
    int score {0};
    Grid grid {};
    KeyHandler keyHandler {};
};

