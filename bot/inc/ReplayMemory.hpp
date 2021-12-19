#include <array>
#include <queue>
#include <memory>

#include "State.hpp"
#include "KeyHandler.hpp"
#include "FIFOBuffer.hpp"

using Action = KeyHandler::Key;

struct Transition
{
    State state;
    Action action;
    State nextState;
    int reward;
};

class ReplayMemory
{
public:
    constexpr static size_t BATCH_SIZE{32};

    void push(const Transition& t);
    std::vector<const Transition*> sample() const;

private:
    constexpr static size_t SIZE{200000};
    FIFOBuffer<Transition> data{SIZE};
};

