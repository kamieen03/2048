#include <opencv2/core/types.hpp>
#include <thread>
#include <opencv2/highgui.hpp>

#include "GridDrawer.hpp"
#include "graphics.hpp"

namespace
{
    cv::Point coordinateToPixel(const Coordinate& c)
    {
        constexpr auto tsize = Tile::TILE_SIZE;
        const auto& [a,b] = c;
        return cv::Point(tsize*b + 10*(b+1), tsize*a + 10*(a+1));
    }

    cv::Point interpolate(const cv::Point& pos1, const cv::Point& pos2, int k, int steps)
    {
        const float t = static_cast<float>(k) / steps;
        return pos1 * (1-t) + pos2 * t;
    }
}

GridDrawer::GridDrawer(std::array<std::array<Tile,4>,4>* tiles,
                       std::function<void()> showBoard)
    : tiles(tiles),
      showBoard(showBoard)
{}

void GridDrawer::refreshImage()
{
    for(int i = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
            refreshTileFace((*tiles)[i][k]);
}

void GridDrawer::refreshTileFace(Tile& t)
{
    const auto origin = coordinateToPixel(t.getPosition());
    graphics::pasteRectangleOntoImage(t.getFace(), gridImage, origin);
}

void GridDrawer::animate(const std::vector<AnimationPair>& animationPairs)
{
    for(int k = 1; k <= ANIMATION_STEPS; k++)
    {
        refreshBaseGridImage();
        for(const auto& ap : animationPairs)
        {
            const auto pos1 = coordinateToPixel(ap.origin);
            const auto pos2 = coordinateToPixel(ap.target);
            const auto pos  = interpolate(pos1, pos2, k, ANIMATION_STEPS);
            graphics::pasteRectangleOntoImage(ap.face, gridImage, pos);
        }
        showBoard();
        cv::waitKey(1);
    }
}

void GridDrawer::updateColorScheme(const ColorScheme& cs)
{
    colorScheme = &cs;
    for(int i = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
           (*tiles)[i][k].updateColorScheme(cs);
    refreshBaseGridImage();
    refreshImage();
}

void GridDrawer::refreshBaseGridImage()
{
    gridImage = cv::Mat{IMAGE_SIZE, IMAGE_SIZE, CV_8UC3, colorScheme->getBackgroundColor()};

    constexpr auto tsize = Tile::TILE_SIZE;
    const auto emptyTileFace = Tile::getEmpetyTileFace();
    for(int i = 0; i < 4; i++)
    {
        for(int k = 0; k < 4; k++)
        {
            const auto origin = coordinateToPixel((*tiles)[i][k].getPosition());
            graphics::pasteRectangleOntoImage(emptyTileFace, gridImage, origin);
        }
    }
}

