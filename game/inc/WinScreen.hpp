#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <string>

#include "CQDecision.hpp"
#include "graphics.hpp"

class WinScreen
{
public:
    // image constants
    static constexpr int HEIGHT   {250};
    static constexpr int WIDTH    {500};
    const cv::Scalar COLOR {CV_RGB(30,150,30)};
    const cv::Scalar OPTION_BACKGROUND {CV_RGB(50,100,250)};

    WinScreen();
    cv::Mat& getImage() {return image;};
    CQDecision getWinDecision();
    void setLeftOption();
    void setRightOption();

private:
    cv::Mat image;
    bool flagLeftOption {true};

    void addWinText();
    void drawDecisionPart();
    void addContinueText();
    void addQuitText();
};

