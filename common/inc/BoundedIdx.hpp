class BoundedIdx
{
public:
    BoundedIdx(int max);
    int getValue() const {return idx;}
    BoundedIdx& operator++();
    BoundedIdx& operator--();
    friend bool operator==(const BoundedIdx& lhs, int rhs);

private:
    int idx {0};
    static constexpr int min {0};
    const int max;
};

