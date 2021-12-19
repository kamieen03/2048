#include "RotationalIdx.hpp"

RotationalIdx::RotationalIdx(int numStates)
    : numStates(numStates)
{}

RotationalIdx& RotationalIdx::operator++()
{
    idx = (idx + 1) % numStates;
    return *this;
}

RotationalIdx& RotationalIdx::operator--()
{
    idx = (idx + numStates - 1) % numStates;
    return *this;
}

