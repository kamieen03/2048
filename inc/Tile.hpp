#pragma once

#include <opencv2/imgproc.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <map>
#include <string>

#include "ColorSchemeReader.hpp"
#include "graphics.hpp"

using Coordinate = std::pair<int,int>;

class Tile
{
public:
    Tile(){};
    Tile(Coordinate c);
    void updateTile(int value);
    void updateColorScheme(const ColorScheme& cs);

    void doubleTile(){updateTile(value*2);};
    cv::Mat getFace() const {return face;};
    int getValue() const {return value;};
    bool empty() const {return value == 0;};
    Coordinate getPosition() const {return position;}

    static cv::Mat getEmpetyTileFace();

    static constexpr int TILE_SIZE {150};

private:
    cv::Scalar getColor(int value);

    static const ColorScheme* colorScheme;
    int value {0};
    Coordinate position;
    cv::Mat face {TILE_SIZE, TILE_SIZE, CV_8UC3, CV_RGB(0,0,0)};
};

