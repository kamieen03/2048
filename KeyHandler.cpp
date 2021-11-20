#include "KeyHandler.hpp"

const std::array<int, 5> KeyHandler::validKeys {119, 97, 115, 100, 27};

KeyHandler::Key KeyHandler::operator()()
{
    int key = 0;
    while(!validKey(key))
        key = cv::waitKey() & 0xFF;
    return static_cast<KeyHandler::Key>(key);
}

bool validKey(int key)
{
    return std::any_of(validKeys.begin(),
                       validKeys.end(),
                       [&key](int vk){return vk == key;});
}
