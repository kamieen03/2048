#include <stdlib.h>
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Grid.hpp"
#include "KeyHandler.hpp"

class Game
{
public:
    Game();
    int run();

private:
    enum class WinDecision
    {
        CONTINUE,
        QUIT
    }

    bool renderElement();
    void showBoard();
    
    bool achieved2048 {false};
    int score {0};
    auto window = cv::namedWindow("2048", CV_WINDOW_AUTOSIZE);

    Grid grid {};
    KeyHandler keyHandler {};
};

