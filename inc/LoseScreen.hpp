#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>

#include "graphics.hpp"

class LoseScreen
{
public:
    // image constants
    static constexpr int HEIGHT   {250};
    static constexpr int WIDTH    {500};
    const cv::Scalar COLOR {CV_RGB(150,30,30)};

    // singleton, so no copying or moving
    LoseScreen(const LoseScreen&)            = delete;
    LoseScreen(LoseScreen&&)                 = delete;
    LoseScreen& operator=(const LoseScreen&) = delete;
    LoseScreen& operator=(LoseScreen&&)      = delete;

    static LoseScreen& get()
    {
        static LoseScreen s;
        return s;
    }
    cv::Mat& getImage() {return image;};

private:
    cv::Mat image;

    LoseScreen();
    void addLoseText();
    void addOkText();
};

