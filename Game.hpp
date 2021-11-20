#include <stdlib.h>
#include <time.h>

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

    int score {0};
    Grid grid {};
    KeyHandler keyHandler {};
};

