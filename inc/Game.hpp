#include <stdlib.h>
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <functional>

#include "Grid.hpp"
#include "WinScreen.hpp"
#include "LoseScreen.hpp"
#include "KeyHandler.hpp"
#include "ColorSchemeReader.hpp"
#include "CQDecision.hpp"
#include "Menu.hpp"
#include "graphics.hpp"
#include "GameState.hpp"

struct GameConfig
{
    bool headless {false};
    bool nonAnimate {false};
};

class Game
{
public:
    Game(const GameConfig& gc);
    int run();

private:
    void renderElement();
    void showBoard();
    bool updateGrid(KeyHandler::Key);
    CQDecision showWinScreen();
    void showLoseScreen();
    void pastePopUpScreen(const cv::Mat& popUpScreen);
    CQDecision handleWinScreenKeys(WinScreen& ws);
    void handleLoseScreenKeys();
    void updateColorScheme(const ColorScheme& cs);
    CQDecision showMenu();
    CQDecision handleMenuKeys();
    void saveState();
    void undoMove();

    const bool isHeadless;
    const bool isAnimated;

    cv::Mat image {Grid::IMAGE_SIZE, Grid::IMAGE_SIZE, CV_8UC3, CV_RGB(0,0,0)};
    bool achieved2048 {false};
    int score {0};
    const std::vector<ColorScheme>& colorSchemes = ColorSchemeReader::getSchemes();
    const ColorScheme* currentColorScheme = &colorSchemes[0];
    Grid grid {*currentColorScheme, [this](){showBoard();}, isAnimated};
    Menu menu {colorSchemes};
    GameStateHistory stateHistory;
};

