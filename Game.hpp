#include <stdlib.h>
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Grid.hpp"
#include "InfoScreen.hpp"
#include "KeyHandler.hpp"
#include "ColorSchemeReader.hpp"
#include "CQDecision.hpp"
#include "Menu.hpp"
#include "graphics.hpp"

class Game
{
public:
    Game();
    int run();

private:
    void renderElement();
    void showBoard();
    bool updateGrid(KeyHandler::Key);
    CQDecision showWinScreen();
    void showLoseScreen();
    void pastePopUpScreen(const cv::Mat& popUpScreen);
    CQDecision handleWinScreenKeys();
    void handleLoseScreenKeys();
    void updateColorScheme(const ColorScheme& cs);
    CQDecision showMenu();
    CQDecision handleMenuKeys();


    cv::Mat image {Grid::IMAGE_SIZE, Grid::IMAGE_SIZE, CV_8UC3, CV_RGB(0,0,0)};
    bool achieved2048 {false};
    int score {0};
    const std::vector<ColorScheme>& colorSchemes = ColorSchemeReader::getSchemes();
    Grid grid {colorSchemes[0]};
    Menu menu {colorSchemes};
};

