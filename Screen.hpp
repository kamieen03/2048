#include <opencv2/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <string>

class WinScreen
{
public:
    enum class WinDecision : int
    {
        CONTINUE,
        QUIT
    };

    // image constants
    static constexpr int HEIGHT   {250};
    static constexpr int WIDTH    {500};
    static const cv::Scalar COLOR;

    // font constants
    static constexpr int    FONT_FACE {cv::FONT_HERSHEY_DUPLEX};
    static constexpr int    FONT_THICKNESS {2};
    static const cv::Scalar FONT_COLOR;
    
    // singleton, so no copying or moving
    WinScreen(const WinScreen&)            = delete;
    WinScreen(WinScreen&&)                 = delete;
    WinScreen& operator=(const WinScreen&) = delete;
    WinScreen& operator=(WinScreen&&)      = delete;

    static WinScreen& get()
    {
        static WinScreen s;
        return s;
    }

    WinDecision getWinDecision();
    cv::Mat& getImage() {return image;};
    void setLeftOption() {flagLeftOption = true;};
    void setRightOption() {flagLeftOption = false;};

private:
    cv::Mat image;
    bool flagLeftOption {true};

    WinScreen();
    void addBorder();
    cv::Size getTextSize(const std::string& text, float font_scale);
    void addText(const std::string& text, const cv::Point& position, float font_scale);
};
