#include <random>

#include "ReplayMemory.hpp"

namespace
{
    std::vector<std::mt19937::result_type> randInts(int n, int k)
    {
        static std::random_device dev;
        static std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, n);

        std::vector<std::mt19937::result_type> ints;
        for(size_t i = 0 ; i < k; i ++)
            ints.push_back(dist(rng));
        return ints;
    }
}

void ReplayMemory::push(const Transition& t)
{
    data.push(t);
}

auto ReplayMemory::sample() const
-> std::vector<const Transition*>
{
    std::vector<const Transition*> arr;
    for(const auto ri : randInts(data.size(), BATCH_SIZE))
    {
        arr.push_back(&data[ri]);
    }
    return arr;
}

