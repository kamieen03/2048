#include <vector>
#include <functional>
#include <array>
#include <iostream>

#include "Tile.hpp"

struct AnimationPair
{
public:
    AnimationPair(const Tile& originTile, const Tile& targetTile)
        : origin(originTile.getPosition()),
          target(targetTile.getPosition()),
          face(originTile.getFace())
    {}
private:
    const Coordinate origin;
    const Coordinate target;
    cv::Mat face;
friend class GridDrawer;
};

class GridDrawer
{
public:
    GridDrawer(std::array<std::array<Tile,4>,4>* tiles, std::function<void()> showBoard);
    void refreshImage();
    void refreshTileFace(Tile& t);
    void animate(const std::vector<AnimationPair>& animationPairs);
    void updateColorScheme(const ColorScheme& cs);
    cv::Mat getImage() const {return gridImage.clone();};

    static constexpr int IMAGE_SIZE = 4 * Tile::TILE_SIZE + 50;
    static constexpr int ANIMATION_STEPS {5};

private:
    void refreshBaseGridImage();

    cv::Mat gridImage {IMAGE_SIZE, IMAGE_SIZE, CV_8UC3, CV_RGB(0,0,0)};
    std::function<void()> showBoard;
    const ColorScheme* colorScheme;
    std::array<std::array<Tile,4>,4>* tiles;
};

