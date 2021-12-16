#include <filesystem>
#include <iostream>

#include "ColorSchemeReader.hpp"

namespace fs = std::filesystem;

ColorScheme::ColorScheme(const std::map<int, cv::Scalar>& tileColors,
                         const cv::Scalar& emptyTileColor,
                         const cv::Scalar& backgroundColor,
                         const std::string& name)
: tileColors(tileColors),
  emptyTileColor(emptyTileColor),
  backgroundColor(backgroundColor),
  name(name)
{}

std::ostream& operator<<(std::ostream& os, const ColorScheme& cs)
{
    os << "Theme " << cs.name << '\n';
    os << "========================\n";
    os << "Tile colors:\n";
    for(const auto& [val, color] : cs.tileColors)
    {
        os << val << ": " << color << '\n';
    }
    os << "Empty tile color:\n";
    os << cs.emptyTileColor << '\n';
    os << "Background color:\n";
    os << cs.backgroundColor;
    return os;
}





void ColorScheme::Builder::setNextTileColor(const std::string& s)
{
    const auto colonIdx = s.find(':');
    const int value = std::stoi(s.substr(0, colonIdx));
    const auto color = stringToColor(s.substr(colonIdx+1));
    tileColors[value] = color;
}

void ColorScheme::Builder::setEmptyTileColor(const std::string& s)
{
    emptyTileColor = stringToColor(s);
}

void ColorScheme::Builder::setBackgroundColor(const std::string& s)
{
    backgroundColor = stringToColor(s);
}

void ColorScheme::Builder::setName(const std::string& name)
{
    this->name = name;
}

ColorScheme ColorScheme::Builder::build()
{
    return ColorScheme(tileColors, emptyTileColor, backgroundColor, name);
}

cv::Scalar ColorScheme::Builder::stringToColor(const std::string& s)
{
    const auto firstComa = s.find(',');
    const auto secondComa = s.rfind(',');
    const auto r = std::stoi(s.substr(0, firstComa));
    const auto g = std::stoi(s.substr(firstComa+1, secondComa-firstComa-1));
    const auto b = std::stoi(s.substr(secondComa+1));
    return CV_RGB(r,g,b);
}





namespace ColorSchemeReader
{
    static bool cached = false;
    static std::vector<ColorScheme> schemes;

    std::vector<ColorScheme>& getSchemes()
    {
        if(cached)
        {
            return schemes;
        }
        const auto path =
            fs::path(__FILE__).parent_path().parent_path() / "color_schemes.co";
        std::ifstream file(path);
        ColorScheme::Builder csb;
        int settingTiles{0};
        bool settingEmptyTile{false}, settingBackground{false};
        for(std::string s; std::getline(file,s); )
        {
            if(s.find("THEME") != std::string::npos)
            {
                csb.setName(s.substr(6));
            }
            else if(s == "TILES")
            {
                settingTiles = 11;
            }
            else if(settingTiles > 0)
            {
                settingTiles--;
                csb.setNextTileColor(s);
            }
            else if(s == "EMPTY TILE")
            {
                settingEmptyTile = true;
            }
            else if(settingEmptyTile)
            {
                settingEmptyTile = false;
                csb.setEmptyTileColor(s);
            }
            else if(s == "BACKGROUND")
            {
                settingBackground = true;
            }
            else if(settingBackground)
            {
                settingBackground = false;
                csb.setBackgroundColor(s);
                schemes.push_back(csb.build());
            }
        }
        cached = true;
        return schemes;
    }
}
