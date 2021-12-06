#include "GameState.hpp"
#include <iostream>

bool operator==(const GameState& g1, const GameState& g2)
{
    return g1.grid == g2.grid and
           g1.achieved2048 == g2.achieved2048;
}

void GameStateHistory::save(const GameState& gs)
{
    if(stateHistory.size() > 0 and gs == stateHistory.front())
    {
        return;
    }
    if(stateHistory.size() == MAX_SIZE)
    {
        stateHistory.pop_back();
    }
    stateHistory.push_front(gs);
}

std::optional<GameState> GameStateHistory::restore()
{
    if(stateHistory.size() == 0)
    {
        return std::nullopt;
    }
    const auto gs = stateHistory.front();
    stateHistory.pop_front();
    return gs;
}

