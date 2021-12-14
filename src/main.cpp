#include <optional>
#include <iostream>

#include "Game.hpp"

constexpr char helpString[] =
    "2048 [-na] [-H] [-h]\n"
    "-na, --non-animate - don't show animations\n"
    "-H, --headless - run in headless mode without game screen\n"
    "-h, --help - show this message\n";

std::optional<GameConfig> parseArguments(int argc, char* argv_[])
{
    GameConfig gc;
    std::vector<std::string> argv(argv_ + 1, argv_ + argc);
    for(const auto& arg : argv)
    {
        if(arg == "-H" or arg == "--headless")
            gc.headless = true;
        if(arg == "-na" or arg == "--non-animate")
            gc.nonAnimate = true;
        if(arg == "-h" or arg == "--help")
        {
            std::cout << helpString << std::endl;
            return std::nullopt;
        }
    }
    return gc;
}

int main(int argc, char* argv[])
{
    const auto gc = parseArguments(argc, argv);
    if(gc)
    {
        Game game(*gc);
        game.run();
    }
    return 0;
}
