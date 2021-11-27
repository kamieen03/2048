#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>

class ColorScheme
{
public:
    ColorScheme(const std::map<int, cv::Scalar>& tileColors,
                const cv::Scalar& emptyTileColor,
                const cv::Scalar& backgroundColor,
                const std::string& name);
    friend std::ostream& operator<<(std::ostream& os, const ColorScheme& cs);

private:
    std::map<int, cv::Scalar> tileColors;
    const cv::Scalar emptyTileColor;
    const cv::Scalar backgroundColor;
    const std::string name;
};

class ColorSchemeBuilder
{
public:
    void setNextTileColor(const std::string& s);
    void setEmptyTileColor(const std::string& s);
    void setBackgroundColor(const std::string& s);
    void setName(const std::string& s);
    ColorScheme build();

private:
    cv::Scalar stringToColor(const std::string& s);

    std::map<int, cv::Scalar> tileColors;
    cv::Scalar emptyTileColor;
    cv::Scalar backgroundColor;
    std::string name;
};

class ColorSchemeReader
{
public:
    static std::vector<ColorScheme> getSchemes();
private:
    static std::vector<ColorScheme> schemes;
    static bool cached;
};
