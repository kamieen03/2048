#include <array>
#include <torch/torch.h>

struct State
{
public:
    State(std::array<std::array<int,4>,4> planeState);
    torch::Tensor& get() {return state;}

private:
    torch::Tensor state;
}

