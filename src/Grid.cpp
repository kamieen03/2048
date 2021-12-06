#include "Grid.hpp"
#include <iostream>

Grid::Grid(const ColorScheme& cs)
{
    for(int i = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
            tiles[i][k] = Tile(std::make_pair(i,k));
    updateColorScheme(cs);
}

std::ostream& operator<<(std::ostream& os, const Grid& g)
{
    for(int i = 0; i < 4; i++)
    {
        for(int k = 0; k < 4; k++)
        {
            os << g.tiles[i][k].getValue() << " ";
        }
        os << '\n';
    }
    return os;
}

void Grid::updateColorScheme(const ColorScheme& cs)
{
    const auto backgroundColor = cs.getBackgroundColor();
    gridImage = cv::Mat{IMAGE_SIZE, IMAGE_SIZE, CV_8UC3, backgroundColor};
    for(int i = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
           tiles[i][k].updateColorScheme(cs);
    refreshImage();
}

void Grid::refreshImage()
{
    for(int i = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
            refreshTileFace(tiles[i][k]);
}

void Grid::refreshTileFace(Tile& t)
{
    const auto& size = Tile::TILE_SIZE;
    const auto& [i, k] = t.getPosition();
    const cv::Point origin(size*k + 10*(k+1), size*i + 10*(i+1));
    graphics::pasteRectangleOntoImage(t.getFace(), gridImage, origin);
}

void Grid::setTile(Tile& t, int value)
{
    t.updateTile(value);
    refreshTileFace(t);
}



bool Grid::update(Key key)
{
    bool changed = false;
    switch (key)
    {
        case Key::UP:
            for(int i = 1; i < 4; i++)
                for(int k = 0; k < 4; k++)
                    changed |= handleTile(tiles[i][k], key);
            break;
        case Key::DOWN:
            for(int i = 2; i >= 0; i--)
                for(int k = 0; k < 4; k++)
                    changed |= handleTile(tiles[i][k], key);
            break;
        case Key::LEFT:
            for(int k = 1; k < 4; k++)
                for(int i = 0; i < 4; i++)
                    changed |= handleTile(tiles[i][k], key);
            break;
        case Key::RIGHT:
            for(int k = 2; k >= 0; k--)
                for(int i = 0; i < 4; i++)
                    changed |= handleTile(tiles[i][k], key);
            break;
    }
    if(changed)
    {
        refreshImage();
    }
    return changed;
}

bool Grid::handleTile(Tile& t, Key key)
{
    if(t.empty())
    {
        return false;
    }

    Tile* t1 = &t;
    Tile* t2;
    bool changed = false;
    while(t2 = nextTile(*t1, key))
    {
        if(t2->getValue() == t1->getValue())
        {
            t2->doubleTile();
            t1->updateTile(0);
            changed = true;          //at most one fusion of one tile
            break;
        }
        else if(t2->empty())
        {
            t2->updateTile(t1->getValue());
            t1->updateTile(0);
            changed = true;
        }
        else
        {
            break;
        }
        t1 = t2;
    }
    return changed;
}

Tile* Grid::nextTile(const Tile& t, Key key)
{
    Coordinate next;
    const auto pos = t.getPosition();
    switch (key)
    {
        case Key::UP:
            next = std::make_pair(pos.first-1, pos.second);
            break;
        case Key::DOWN:
            next = std::make_pair(pos.first+1, pos.second);
            break;
        case Key::LEFT:
            next = std::make_pair(pos.first, pos.second-1);
            break;
        case Key::RIGHT:
            next = std::make_pair(pos.first, pos.second+1);
            break;
    }

    if(next.first >= 0 and next.first < 4 and next.second >= 0 and next.second < 4)
        return &tiles[next.first][next.second];
    return nullptr;
}

bool Grid::has2048() const
{
    for(int i = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
            if(tiles[i][k].getValue() == 2048)
                return true;
    return false;
}

bool Grid::isFull() const
{
    for(int i = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
            if(tiles[i][k].getValue() == 0)
                return false;
    return true;
}

bool Grid::canMove()
{
    if(!isFull())
    {
        return true;
    }

    const std::array<Key, 4> moveKeys {Key::UP, Key::DOWN, Key::LEFT, Key::RIGHT};
    const Tile *t1, *t2;

    for(int i = 0; i < 4; i++)
    {
        for(int k = 0; k < 4; k++)
        {
            t1 = &tiles[i][k];
            for(const auto& key : moveKeys)
            {
                t2 = nextTile(*t1, key);
                if(t2 and t1->getValue() == t2->getValue())  // tiles can fuse
                {
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<Tile*> Grid::getFreeTiles()
{
    std::vector<Tile*> freeTiles;
    for(int i = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
            if(tiles[i][k].getValue() == 0)
                freeTiles.push_back(&tiles[i][k]);
    return freeTiles;
}

bool operator==(const Grid& g1, const Grid& g2)
{
    for(int i = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
            if(g1.tiles[i][k].getValue() != g2.tiles[i][k].getValue())
                return false;
    return true;
}

