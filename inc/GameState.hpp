#include <deque>
#include <optional>

#include "Grid.hpp"

struct GameState
{
    Grid grid;
    bool achieved2048;
    friend bool operator==(const GameState& g1, const GameState& g2);
};

class GameStateHistory
{
public:
    void save(const GameState& gs);
    std::optional<GameState> restore();

    static constexpr size_t MAX_SIZE {10};

private:
    std::deque<GameState> stateHistory;
};

