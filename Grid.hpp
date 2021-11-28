#include <algorithm>
#include <vector>
#include <array>
#include <functional>
#include <optional>
#include <opencv2/core/types.hpp>

#include "Tile.hpp"
#include "KeyHandler.hpp"
#include "ColorSchemeReader.hpp"

using Coordinate = std::pair<int,int>;
using Key = KeyHandler::Key;

class Grid
{
public:
    Grid(const ColorScheme& cs);
    bool has2048() const;
    bool isFull() const;
    bool canMove();
    cv::Mat getImage() const {return gridImage.clone();};
    std::vector<Tile*> getFreeTiles();
    bool update(KeyHandler::Key key);
    void setTile(Tile& t, int value);
    void updateColorScheme(const ColorScheme& cs);

    static constexpr int IMAGE_SIZE = 4 * Tile::TILE_SIZE + 50;

private:
    std::optional<Tile*> nextTile(const Tile& t, Key key);
    bool handleTile(Tile& t, KeyHandler::Key key);
    void refreshImage();
    void refreshTileFace(Tile& t);
    void printGrid() const;

    std::array<std::array<Tile,4>,4> tiles;
    cv::Mat gridImage {IMAGE_SIZE, IMAGE_SIZE, CV_8UC3, CV_RGB(0,0,0)};
};

