#include <algorithm>
#include <vector>
#include <array>
#include <functional>
#include <optional>
#include <opencv2/core/types.hpp>

#include "Tile.hpp"
#include "KeyHandler.hpp"
#include "ColorSchemeReader.hpp"
#include "graphics.hpp"

using Coordinate = std::pair<int,int>;
using Key = KeyHandler::Key;

class Grid
{
public:
    Grid(const ColorScheme& cs);
    void updateColorScheme(const ColorScheme& cs);
    void setTile(Tile& t, int value);
    bool update(KeyHandler::Key key);

    bool has2048() const;
    bool isFull() const;
    bool canMove();
    std::vector<Tile*> getFreeTiles();
    cv::Mat getImage() const {return gridImage.clone();};

    static constexpr int IMAGE_SIZE = 4 * Tile::TILE_SIZE + 50;

private:
    void refreshImage();
    void refreshTileFace(Tile& t);
    bool handleTile(Tile& t, KeyHandler::Key key);
    Tile* nextTile(const Tile& t, Key key);

    std::array<std::array<Tile,4>,4> tiles;
    cv::Mat gridImage {IMAGE_SIZE, IMAGE_SIZE, CV_8UC3, CV_RGB(0,0,0)};
};

