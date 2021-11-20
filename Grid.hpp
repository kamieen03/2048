#include <algorithm>
#include <vector>
#include <array>

#include "Tile.hpp"

class Grid
{
public:
    bool has2048()
    {
        std::any()
    }

    bool isFull()
    {
        return std::all ...
    }

    std::vector<Tile&> getFreeTiles()
    {

    }

    bool setTile(Tile& tile, int number)
    {
        tile.number = number;
        tile.color = tile.setColor(number);
    }

private:
    std::array<std::aray<Tile,4>,4> tiles;
};
