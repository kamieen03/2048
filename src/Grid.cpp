#include "Grid.hpp"
#include <iostream>

Grid::Grid(const ColorScheme& cs, std::function<void()> showBoardFunction, bool isAnimated)
    : drawer(GridDrawer(&tiles, showBoardFunction)),
      isAnimated(isAnimated)
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
    drawer.updateColorScheme(cs);
}

void Grid::setTile(Tile& t, int value)
{
    t.updateTile(value);
    drawer.refreshTileFace(t);
}


bool Grid::update(Key key)
{
    bool changedAtLeastOnce = false;
    bool changedInThisRound = true;
    std::vector<AnimationPair> animationPairs;
    std::vector<TileUpdate> tileUpdates;
    recomputeAllowedFusions();

    while(changedInThisRound)
    {
        animationPairs.clear();
        tileUpdates.clear();

        changedInThisRound = computeUpdatesAndAnimationsForAllTiles(key, animationPairs, tileUpdates);
        changedAtLeastOnce |= changedInThisRound;

        if(changedInThisRound and isAnimated)
        {
            drawer.animate(animationPairs);
        }
        applyUpdates(tileUpdates);
    }
    if(changedAtLeastOnce)
    {
        drawer.refreshImage();
    }
    return changedAtLeastOnce;
}

bool Grid::computeUpdatesAndAnimationsForAllTiles(
        Key key, std::vector<AnimationPair>& animationPairs,
        std::vector<TileUpdate>& tileUpdates)
{
    bool changed = false;
    auto htf = [this, key, &animationPairs, &tileUpdates](Tile& tile, int& allowedFusionNumber){
        return handleTile(tile, key, allowedFusionNumber, animationPairs, tileUpdates);
    };

    switch (key)
    {
        case Key::UP:
            for(int i = 0; i < 4; i++)
                for(int k = 0; k < 4; k++)
                    changed |= htf(tiles[i][k], allowedFusions.column[k]);
            break;
        case Key::DOWN:
            for(int i = 3; i >= 0; i--)
                for(int k = 0; k < 4; k++)
                    changed |= htf(tiles[i][k], allowedFusions.column[k]);
            break;
        case Key::LEFT:
            for(int k = 0; k < 4; k++)
                for(int i = 0; i < 4; i++)
                    changed |= htf(tiles[i][k], allowedFusions.row[i]);
            break;
        case Key::RIGHT:
            for(int k = 3; k >= 0; k--)
                for(int i = 0; i < 4; i++)
                    changed |= htf(tiles[i][k], allowedFusions.row[i]);
            break;
    }
    return changed;
}

bool Grid::handleTile(Tile& t, Key key, int& allowedFusionNumber,
                      std::vector<AnimationPair>& animationPairs,
                      std::vector<TileUpdate>& tileUpdates)
{
    if(t.empty())
    {
        return false;
    }

    Tile* const tn = nextTile(t, key);
    if(tn)
    {
        if(tn->getValue() == t.getValue() and allowedFusionNumber > 0)
        {
            tileUpdates.push_back([tn](){tn->doubleTile();});
            tileUpdates.push_back([&t](){t.updateTile(0);});
            allowedFusionNumber--;
            animationPairs.push_back(AnimationPair{t, *tn});
            return true;
        }
        else if(tn->empty())
        {
            tileUpdates.push_back([tn, &t](){tn->updateTile(t.getValue());});
            tileUpdates.push_back([&t](){t.updateTile(0);});
            animationPairs.push_back(AnimationPair{t, *tn});
            return true;
        }
    }
    animationPairs.push_back(AnimationPair{t, t});
    return false;
}

void Grid::applyUpdates(const std::vector<TileUpdate>& tileUpdates)
{
    for(const auto& update : tileUpdates)
    {
       update();
    }
}

void Grid::recomputeAllowedFusions()
{
    for(int line = 0; line < 4; line++)
    {
        allowedFusions.column[line] = recomputeAllowedFusionsInLine(line, false);
        allowedFusions.row[line]    = recomputeAllowedFusionsInLine(line, true);
    }
}

int Grid::recomputeAllowedFusionsInLine(int line, bool rowOrder)
{
    int pairs {0};
    int previousValue {0}, currentValue {0};
    const Tile* t;
    for(int k = 0; k < 4; k++)
    {
        if(rowOrder)
            t = &tiles[line][k];
        else
            t = &tiles[k][line];

        if((currentValue = t->getValue()) > 0)
        {
            if(currentValue == previousValue)
            {
                pairs++;
                previousValue = 0;
            }
            else
            {
                previousValue = currentValue;
            }
        }
    }
    return pairs;
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

std::array<std::array<int,4>,4> Grid::getAbstractState() const
{
    std::array<std::array<int,4>,4> state;
    for(int i = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
            state[i][k] = tiles[i][k].getValue();
    return state;
}

bool operator==(const Grid& g1, const Grid& g2)
{
    for(int i = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
            if(g1.tiles[i][k].getValue() != g2.tiles[i][k].getValue())
                return false;
    return true;
}

