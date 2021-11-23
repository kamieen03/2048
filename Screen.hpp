#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
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
    static const cv::Scalar OPTION_BACKGROUND;

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
    void setLeftOption();
    void setRightOption();

private:
    cv::Mat image;
    bool flagLeftOption {true};

    WinScreen();
    void addWinText(float fontScale);
    void addContinueText(float fontScale);
    void addQuitText(float fontScale);
    void addBorder();
    void addOptionBackgroudRectangle(cv::Point p1, const cv::Size& size, bool option);
    cv::Size getTextSize(const std::string& text, float fontScale);
    void addText(const std::string& text, const cv::Point& position, float fontScale);
};
