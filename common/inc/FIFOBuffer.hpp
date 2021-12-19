#include <vector>

template <typename T>
class FIFOBuffer
{
public:
    FIFOBuffer(int maxSize)
        : maxSize(maxSize)
    {}

    void push(const T& element)
    {
        if(data.size() < maxSize)
            data.push_back(element);
        else
            data[idx] = element;
        idx = (idx+1) % maxSize;
    }

    const T& operator[](size_t idx) const
    {
        return data[idx];
    }

    auto size() const { return data.size(); }

private:
    int idx{0};
    const int maxSize;
    std::vector<T> data;
};


