#include <algorithm>
#include <vector>
#include <array>
#include <functional>
#include <optional>
#include <opencv2/core/types.hpp>

#include "Tile.hpp"
#include "KeyHandler.hpp"

using Coordinate = std::pair<int,int>;

class Grid
{
public:
    Grid();
    bool has2048() const;
    bool isFull() const;
    cv::Mat getImage() const {return gridImage.clone();};
    std::vector<Coordinate> getFreeTilesCoordinates() const;
    bool update(KeyHandler::Key key);
    void setTile(const Coordinate& c, int value);

    static constexpr int IMAGE_SIZE = 4 * Tile::TILE_SIZE + 50;

private:
    std::optional<Coordinate> nextCoordinate(const Coordinate& c, KeyHandler::Key key);
    Tile& getTile(const Coordinate& c) {return tiles[c.first][c.second];};
    bool handleTile(Coordinate c, KeyHandler::Key key);
    void refreshImage();
    void refreshTileFace(const Coordinate& c);
    void printGrid() const;

    std::array<std::array<Tile,4>,4> tiles;
    static const cv::Scalar backgroundColor;
    static const std::array<std::array<Coordinate,4>,4> coordinateGrid;
    cv::Mat gridImage {IMAGE_SIZE, IMAGE_SIZE, CV_8UC3, backgroundColor};
};

