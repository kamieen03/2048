#include "BoundedIdx.hpp"

BoundedIdx::BoundedIdx(int max)
    : max(max)
{}

BoundedIdx& BoundedIdx::operator++()
{
    if(idx < max) idx++;
    return *this;
}

BoundedIdx& BoundedIdx::operator--()
{
    if(idx > min) idx--;
    return *this;
}

bool operator==(const BoundedIdx& lhs, int rhs)
{
    return lhs.getValue() == rhs;
}

