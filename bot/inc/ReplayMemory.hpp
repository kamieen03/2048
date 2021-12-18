#include <array>
#include <memory>

#include "State.hpp"
#include "KeyHandler.hpp"

struct Transition
{
    using Action = KeyHandler::Key;
    const State state;
    const Action action;
    const State nextState;
    const int reward;
};

class ReplayMemory
{
public:
    ReplayMemory();
    std::array<const Transition* const, BATCH_SIZE> sample const ();

    constexpr static size_t BATCH_SIZE{32};

private:
    class CircularBuffer;
    std::unique_ptr<CircularBuffer> buffer;
};

