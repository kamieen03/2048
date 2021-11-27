#include "Tile.hpp"
#include <iostream>

const cv::Scalar Tile::FONT_COLOR = CV_RGB(0,0,0);
const ColorScheme* Tile::colorScheme {nullptr};

void Tile::updateTile(int val)
{

    value = val;
    setFaceColor(value);
    if(value != 0)
    {
        setText(value);
    }
}

void Tile::setText(int val)
{
    int baseline;
    cv::Size s = cv::getTextSize(std::to_string(val),
                                 FONT_FACE,
                                 FONT_SCALE,
                                 FONT_THICKNESS,
                                 &baseline);
    cv::putText(face,
                std::to_string(val),
                cv::Point((TILE_SIZE - s.width) / 2, (TILE_SIZE + s.height) / 2), // bottom-left corner
                FONT_FACE,
                FONT_SCALE,
                FONT_COLOR,
                FONT_THICKNESS);
}

void Tile::setFaceColor(int val)
{
    cv::Scalar color;
    if(val == 0)
    {
        color = colorScheme->getEmptyTileColor();
    }
    else
    {
        const auto& colorMap = colorScheme->getTileColors();
        const auto it = colorMap.find(val);
        color = (it != colorMap.end()) ? it->second : colorMap.at(2048);
    }
    face = cv::Mat(TILE_SIZE, TILE_SIZE, CV_8UC3, color);
}

void Tile::updateColorScheme(const ColorScheme& cs)
{
    colorScheme = &cs;
    updateTile(value);
}
