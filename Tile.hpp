#include <opencv2/imgproc.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <map>
#include <string>

#include "ColorSchemeReader.hpp"

class Tile
{
public:
    void updateTile(int value);
    void doubleTile(){updateTile(value*2);};
    cv::Mat getFace() {return face;};
    int getValue() const {return value;};
    bool empty() const {return value == 0;};
    void updateColorScheme(const ColorScheme& cs);

    static constexpr int TILE_SIZE {150};

private:
    void setFaceColor(int value);
    void setText(int val);

    static constexpr int FONT_FACE {cv::FONT_HERSHEY_DUPLEX};
    static constexpr float FONT_SCALE {2};
    static constexpr int FONT_THICKNESS {2};
    static const cv::Scalar FONT_COLOR;
    static const ColorScheme* colorScheme;

    int value {0};
    cv::Mat face {TILE_SIZE, TILE_SIZE, CV_8UC3, CV_RGB(0,0,0)};


};
