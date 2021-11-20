#include <opencv2/imgproc.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <map>
#include <string>

class Tile
{
public:
    Tile(){};
    Tile(cv::Mat& mat)
    {
        face = mat;
    }
    int getValue() const {return value;};
    void updateTile(int value);

private:
    void setFace(int value);

    static const std::map<int, cv::Scalar> colorMap;

    int value {0};
    cv::Mat face;
};
