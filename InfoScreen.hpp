#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <string>


class InfoScreen
{
public:
    // image constants
    static constexpr int HEIGHT   {250};
    static constexpr int WIDTH    {500};

    static constexpr int    FONT_FACE {cv::FONT_HERSHEY_DUPLEX};
    static constexpr int    FONT_THICKNESS {2};
    static const cv::Scalar FONT_COLOR;

    virtual cv::Mat& getImage() = 0;

protected:
    void addBorder(cv::Mat& img);
    cv::Size getTextSize(const std::string& text, float fontScale);
    void addText(cv::Mat& img, const std::string& text, const cv::Point& position, float fontScale);
};


class WinScreen : public InfoScreen
{
public:
    enum class WinDecision : int
    {
        CONTINUE,
        QUIT
    };

    // image constants
    const cv::Scalar COLOR {CV_RGB(30,150,30)};
    const cv::Scalar OPTION_BACKGROUND {CV_RGB(50,100,250)};

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
    cv::Mat& getImage() {return image;};
    WinDecision getWinDecision();
    void setLeftOption();
    void setRightOption();

private:
    cv::Mat image;
    bool flagLeftOption {true};

    WinScreen();
    void addWinText(float fontScale);
    void addContinueText(float fontScale);
    void addQuitText(float fontScale);
    void addOptionBackgroudRectangle(cv::Point p1, const cv::Size& size, bool option);
};


class LoseScreen : public InfoScreen
{
public:
    // image constants
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
    void addLoseText(float fontScale);
    void addOkText(float fontScale);
};
