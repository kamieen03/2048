#pragma once

#include <opencv2/highgui.hpp>
#include <array>
#include <algorithm>

class KeyHandler
{
public:
    enum Key
    {
        UP = 119,
        LEFT = 97,
        DOWN = 115,
        RIGHT = 100,
        QUIT = 27,
        ENTER = 13
    };
    KeyHandler::Key operator()();

private:
    bool validInGameKey(int);
};
