#include "Grid.hpp"
#include <iostream>

Grid::Grid(const ColorScheme& cs)
{
    for(int i = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
            tiles[i][k] = Tile(std::make_pair(i,k));
    updateColorScheme(cs);
}

std::optional<Tile*> Grid::nextTile(const Tile& t, Key key)
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
    return std::nullopt;
}

bool Grid::handleTile(Tile& t, Key key)
{
    if(t.empty())
    {
        return false;
    }

    Tile* t1 = &t;
    std::optional<Tile*> _t2;
    Tile* t2;
    bool changed = false;
    while(_t2 = nextTile(*t1, key))
    {
        t2 = _t2.value();
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

void Grid::refreshImage()
{
    for(int i = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
            refreshTileFace(tiles[i][k]);
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
    const std::array<Key, 4> moveKeys {Key::UP, Key::DOWN, Key::LEFT, Key::RIGHT};

    Tile* t1;
    std::optional<Tile*> t2;

    for(int i = 0; i < 4; i++)
    {
        for(int k = 0; k < 4; k++)
        {
            t1 = &tiles[i][k];
            for(const auto& key : moveKeys)
            {
                t2 = nextTile(*t1, key);
                if(t2 and t1->getValue() == (*t2)->getValue())
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

void Grid::setTile(Tile& t, int value)
{
    t.updateTile(value);
    refreshTileFace(t);
}

void Grid::refreshTileFace(Tile& t)
{
    const auto& [i, k] = t.getPosition();
    const auto& size = Tile::TILE_SIZE;
    auto dst = gridImage(cv::Rect(size*k+10*(k+1), size*i+10*(i+1), size, size));
    t.getFace().copyTo(dst);
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

