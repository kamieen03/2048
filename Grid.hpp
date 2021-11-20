#include <algorithm>
#include <vector>
#include <array>
#include <functional>
#include <opencv2/core/types.hpp>

#include "Tile.hpp"

class Grid
{
public:
    Grid();
    bool has2048();
    bool isFull();
    std::vector<std::reference_wrapper<Tile>> getFreeTiles();
    bool setTile(Tile& tile, int number);
    cv::Mat getImage() {return image;};

private:
    std::array<std::array<Tile,4>,4> tiles;
    const static cv::Scalar backgroundColor;
    cv::Mat image {450, 450, CV_8UC3, backgroundColor};
};

