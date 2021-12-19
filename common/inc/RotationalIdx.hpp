class RotationalIdx
{
public:
    RotationalIdx(int numStates);
    int getValue() const {return idx;}
    RotationalIdx& operator++();
    RotationalIdx& operator--();
private:
    int idx {0};
    const int numStates;
};

