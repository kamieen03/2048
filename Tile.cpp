#include "Tile.hpp"

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


void Tile::updateTile(int value)
{
    value = value;
    setFace(value);
    if(value != 0)
    {
        cv::putText(face,
                    std::to_string(value),
                    cv::Point(40, 40),
                    cv::FONT_HERSHEY_DUPLEX,
                    1.0,
                    CV_RGB(0, 0, 0),
                    2);
    }
}

void Tile::setFace(int number)
{
    const auto it = colorMap.find(number);
    const auto color = (it != colorMap.end()) ? it->second : colorMap.at(2048);
    face = cv::Mat(100, 100, CV_8UC3, color);
}

