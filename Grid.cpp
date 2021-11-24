#include "Grid.hpp"
#include <iostream>

const cv::Scalar Grid::backgroundColor {CV_RGB(180,0,40)};

const std::array<std::array<Coordinate,4>,4> Grid::coordinateGrid = []
{
    std::array<std::array<Coordinate,4>,4> cg;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            cg[i][j] = std::make_pair(i,j);
    return cg;
}();


Grid::Grid()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            refreshTileFace(std::make_pair(i,j));
}

std::optional<Coordinate> Grid::nextCoordinate(const Coordinate& c, KeyHandler::Key key) const
{
    Coordinate next;
    switch (key)
    {
        case KeyHandler::Key::UP:
            next = std::make_pair(c.first-1, c.second);
            break;
        case KeyHandler::Key::DOWN:
            next = std::make_pair(c.first+1, c.second);
            break;
        case KeyHandler::Key::LEFT:
            next = std::make_pair(c.first, c.second-1);
            break;
        case KeyHandler::Key::RIGHT:
            next = std::make_pair(c.first, c.second+1);
            break;
    }

    if(next.first >= 0 and next.first < 4 and next.second >= 0 and next.second < 4)
        return next;
    return std::nullopt;
}

bool Grid::handleTile(Coordinate c, KeyHandler::Key key)
{
    if(getTile(c).empty())
    {
        return false;
    }

    std::optional<Coordinate> _n;
    Coordinate n;
    bool changed = false;
    while(_n = nextCoordinate(c, key))
    {
        n = _n.value();
        if(getTile(n).getValue() == getTile(c).getValue())
        {
            getTile(n).doubleTile();
            getTile(c).updateTile(0);
            changed = true;          //at most one fusion of one tile
            break;
        }
        else if(getTile(n).empty())
        {
            getTile(n).updateTile(getTile(c).getValue());
            getTile(c).updateTile(0);
            changed = true;
        }
        else
        {
            changed |= false;
            break;
        }
        c = n;
    }
    return changed;
}

bool Grid::update(KeyHandler::Key key)
{
    bool changed = false;
    switch (key)
    {
        case KeyHandler::Key::UP:
            for(int i = 1; i < 4; i++)
                for(int k = 0; k < 4; k++)
                    changed |= handleTile(coordinateGrid[i][k], key);
            break;
        case KeyHandler::Key::DOWN:
            for(int i = 2; i >= 0; i--)
                for(int k = 0; k < 4; k++)
                    changed |= handleTile(coordinateGrid[i][k], key);
            break;
        case KeyHandler::Key::LEFT:
            for(int k = 1; k < 4; k++)
                for(int i = 0; i < 4; i++)
                    changed |= handleTile(coordinateGrid[i][k], key);
            break;
        case KeyHandler::Key::RIGHT:
            for(int k = 2; k >= 0; k--)
                for(int i = 0; i < 4; i++)
                    changed |= handleTile(coordinateGrid[i][k], key);
            break;
    }
    refreshImage();
    return changed;
}

void Grid::refreshImage()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            refreshTileFace(coordinateGrid[i][j]);
}

bool Grid::has2048() const
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(tiles[i][j].getValue() == 2048)
                return true;
    return false;
}

bool Grid::isFull() const
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(tiles[i][j].getValue() == 0)
                return false;
    return true;
}

bool Grid::canMove()
{
    const std::array<Key, 4> moveKeys {Key::UP, Key::DOWN, Key::LEFT, Key::RIGHT};

    Coordinate t;
    std::optional<Coordinate> n;

    for(int i = 0; i < 4; i++)
    {
        for(int k = 0; k < 4; k++)
        {
            for(const auto& key : moveKeys) 
            {
                t = coordinateGrid[i][k];
                n = nextCoordinate(t, key);
                if(n and getTile(t).getValue() == getTile(*n).getValue())
                {
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<Coordinate> Grid::getFreeTilesCoordinates() const
{
    std::vector<Coordinate> freeTiles;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(tiles[i][j].getValue() == 0)
                freeTiles.push_back(std::make_pair(i,j));
    return freeTiles;
}

void Grid::setTile(const Coordinate& c, int value)
{
    getTile(c).updateTile(value);
    refreshTileFace(c);
}

void Grid::refreshTileFace(const Coordinate& c)
{
    const auto& [i, k] = c;
    const auto& size = Tile::TILE_SIZE;
    auto dst = gridImage(cv::Rect(size*k+10*(k+1), size*i+10*(i+1), size, size));
    tiles[i][k].getFace().copyTo(dst);
}

