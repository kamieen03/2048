#pragma once

#include <algorithm>
#include <vector>
#include <array>
#include <map>
#include <functional>
#include <optional>
#include <opencv2/core/types.hpp>
#include <ostream>
#include <functional>

#include "Tile.hpp"
#include "KeyHandler.hpp"
#include "ColorSchemeReader.hpp"
#include "graphics.hpp"
#include "GridDrawer.hpp"

using Coordinate = std::pair<int,int>;
using Key = KeyHandler::Key;

class Grid
{
public:
    Grid(const ColorScheme& cs, std::function<void()> showBoardFunction, bool isAnimated);
    friend std::ostream& operator<<(std::ostream& os, const Grid& g);
    void updateColorScheme(const ColorScheme& cs);
    void setTile(Tile& t, int value);
    bool update(KeyHandler::Key key);

    bool has2048() const;
    bool isFull() const;
    bool canMove();
    std::vector<Tile*> getFreeTiles();
    cv::Mat getImage() const {return drawer.getImage();};
    std::array<std::array<int,4>,4> getAbstractState() const;
    friend bool operator==(const Grid& g1, const Grid& g2);

    static constexpr int IMAGE_SIZE = GridDrawer::IMAGE_SIZE;

private:
    using TileUpdate = std::function<void()>;
    friend GridDrawer;

    bool computeUpdatesAndAnimationsForAllTiles(
            Key key, std::vector<AnimationPair>& animationPairs,
            std::vector<TileUpdate>& tileUpdates);
    bool handleTile(Tile& t, Key key, int& allowedFusionNumber,
                    std::vector<AnimationPair>& animationPairs,
                    std::vector<TileUpdate>& tileUpdates);
    void applyUpdates(const std::vector<TileUpdate>& tileUpdates);
    void recomputeAllowedFusions();
    int recomputeAllowedFusionsInLine(int line, bool rowOrder);
    Tile* nextTile(const Tile& t, Key key);

    std::array<std::array<Tile,4>,4> tiles;
    struct AllowedFusions
    {
        std::array<int, 4> column;
        std::array<int, 4> row;
    } allowedFusions;
    GridDrawer drawer;
    bool isAnimated;
};

