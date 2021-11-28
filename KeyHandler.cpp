#include "KeyHandler.hpp"

KeyHandler::Key KeyHandler::handle() const
{
    int key = 0;
    while(!validInGameKey(key))
        key = cv::waitKey() & 0xFF;
    return KeyHandler::Key(key);
}

bool KeyHandler::validInGameKey(int key) const
{
    static constexpr std::array<Key, 5> validKeys
    {
        Key::UP, Key::DOWN, Key::LEFT, Key::RIGHT, Key::QUIT
    };
    return std::any_of(validKeys.begin(),
                       validKeys.end(),
                       [&key](int vk){return vk == key;});
}
