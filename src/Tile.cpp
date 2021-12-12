#include "Tile.hpp"
#include <iostream>

const ColorScheme* Tile::colorScheme {nullptr};

Tile::Tile(Coordinate c):
    position(c)
{}

void Tile::updateTile(int val)
{
    value = val;
    const auto color = getColor(value);
    const auto text = (value == 0) ? "" : std::to_string(value);
    face = graphics::getColoredRectangleWithCenteredText(
            TILE_SIZE, TILE_SIZE, color, text, 2);
}

cv::Scalar Tile::getColor(int val)
{
    if(val == 0)
    {
        return colorScheme->getEmptyTileColor();
    }
    else
    {
        const auto& colorMap = colorScheme->getTileColors();
        const auto it = colorMap.find(val);
        return (it != colorMap.end()) ? it->second : colorMap.at(2048);
    }
}

void Tile::updateColorScheme(const ColorScheme& cs)
{
    colorScheme = &cs;
    updateTile(value);
}

cv::Mat Tile::getEmpetyTileFace()
{
    const auto color = colorScheme->getEmptyTileColor();
    return graphics::getColoredRectangleWithCenteredText(
            TILE_SIZE, TILE_SIZE, color, "");
}

