#include "Tile.hpp"
#include <iostream>

const std::map<int, cv::Scalar> Tile::colorMap = []
{
    std::map<int, cv::Scalar> colorMap;
    colorMap[0] = CV_RGB(103,180,191);      // empty tile
    colorMap[2] = CV_RGB(250, 250, 110);
    colorMap[4] = CV_RGB(251, 233, 88);
    colorMap[8] = CV_RGB(252, 216, 67);
    colorMap[16] = CV_RGB(253, 198, 46);
    colorMap[32] = CV_RGB(254, 179, 26);
    colorMap[64] = CV_RGB(254, 160, 1);
    colorMap[128] = CV_RGB(253, 140, 0);
    colorMap[256] = CV_RGB(252, 118, 0);
    colorMap[512] = CV_RGB(250, 95, 0);
    colorMap[1024] = CV_RGB(247, 66, 7);
    colorMap[2048] = CV_RGB(243, 20, 20);
    return colorMap;
}();

const cv::Scalar Tile::FONT_COLOR = CV_RGB(0,0,0);


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
    const auto it = colorMap.find(val);
    const auto color = (it != colorMap.end()) ? it->second : colorMap.at(2048);
    face = cv::Mat(TILE_SIZE, TILE_SIZE, CV_8UC3, color);
}

