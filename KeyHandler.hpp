#include <opencv2/highgui.hpp>
#include <array>
#include <algorithm>

class KeyHandler
{
public:
    enum class Key: int
    {
        UP = 119,
        LEFT = 97,
        DOWN = 115,
        RIGHT = 100,
        QUIT = 27
    }

    Key operator()();

private:
    const static std::array<int, 5> validKeys;
}
