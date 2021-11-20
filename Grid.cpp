#include "Grid.hpp"

const cv::Scalar Grid::backgroundColor = []
{
    return CV_RGB(0,0,40);
}();

Grid::Grid()
{
    for(size_t i = 0; i < 4; i++)
    {
        for(size_t j = 0; j < 4; j++)
        {
            tiles[i][j] = Tile(image(cv::Rect(
                            100*i+10, 100*j+10,
                            100*(i+1)+10, 100*(j+1) + 10)));
            tiles[i][j].updateTile(0);
        }
    }
}

bool Grid::has2048()
{
    for(size_t i = 0; i < 4; i++)
        for(size_t j = 0; j < 4; j++)
            if(tiles[i][j].getValue() == 2048)
                return true;
    return false;
}

bool Grid::isFull()
{
    for(size_t i = 0; i < 4; i++)
        for(size_t j = 0; j < 4; j++)
            if(tiles[i][j].getValue() == 0)
                return false;
    return true;
}

std::vector<std::reference_wrapper<Tile>> Grid::getFreeTiles()
{
    std::vector<std::reference_wrapper<Tile>> freeTiles;
    for(size_t i = 0; i < 4; i++)
        for(size_t j = 0; j < 4; j++)
            if(tiles[i][j].getValue() == 0)
                freeTiles.push_back(std::ref(tiles[i][j]));
    return freeTiles;
}

void Grid::setTile(Tile& tile, int number)
{
    tile.updateTile(number);
}

