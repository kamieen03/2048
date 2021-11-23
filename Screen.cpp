#include "Screen.hpp"

const cv::Scalar WinScreen::COLOR {CV_RGB(30,150,30)};
const cv::Scalar WinScreen::FONT_COLOR {CV_RGB(0,0,0)};
const cv::Scalar WinScreen::OPTION_BACKGROUND {CV_RGB(50,100,250)};

WinScreen::WinScreen()
{
    image = cv::Mat{HEIGHT, WIDTH, CV_8UC3, COLOR}; 
    addBorder();

    const int bigFont = 2;
    const int smallFont = 1;

    addWinText(bigFont);
    addContinueText(smallFont);
    addQuitText(smallFont);
}

void WinScreen::addWinText(float fontScale)
{
    const std::string text {"You win!"};
    const auto size = getTextSize(text, fontScale);
    const auto pos = cv::Point(
            (WIDTH - size.width) / 2, (HEIGHT + size.height) / 3);
    addText(text, pos, fontScale); 
}

void WinScreen::addContinueText(float fontScale)
{
    const std::string text {"Continue"};
    const auto size = getTextSize(text, fontScale);
    const auto pos = cv::Point(
            (WIDTH - size.width) / 4, (HEIGHT + size.height) * 2/3);
    addOptionBackgroudRectangle(pos, size, flagLeftOption);
    addText(text, pos, fontScale); 
}

void WinScreen::addQuitText(float fontScale)
{
    const std::string text {"Quit"};
    const auto size = getTextSize(text, fontScale);
    const auto pos = cv::Point(
            (WIDTH - size.width) * 3/4, (HEIGHT + size.height) * 2/3);
    addOptionBackgroudRectangle(pos, size, !flagLeftOption);
    addText(text, pos, fontScale); 
}

void WinScreen::addBorder()
{
    cv::rectangle(image,
                  cv::Point(0,0),
                  cv::Point(WIDTH, HEIGHT),
                  CV_RGB(100, 20, 200),
                  10); //thickness
}

void WinScreen::addOptionBackgroudRectangle(cv::Point p1, const cv::Size& size, bool option)
{
    const auto color = option ? OPTION_BACKGROUND : COLOR;
    const auto p2 = p1 + cv::Point(size.width+6, -size.height-6);
    p1 += cv::Point(-6,6);
    cv::rectangle(image, p1, p2, color, cv::FILLED);
}

cv::Size WinScreen::getTextSize(const std::string& text, float fontScale)
{
    int baseline {0};
    return cv::getTextSize(text,
                           FONT_FACE, fontScale, FONT_THICKNESS,
                           &baseline);
}

void WinScreen::addText(const std::string& text, const cv::Point& position, float fontScale)
{
    cv::putText(image,
                text,
                position,
                FONT_FACE, fontScale, FONT_COLOR, FONT_THICKNESS * fontScale);
}

void WinScreen::setLeftOption()
{
    flagLeftOption = true;
    addContinueText(1);
    addQuitText(1);
}

void WinScreen::setRightOption()
{
    flagLeftOption = false;
    addContinueText(1);
    addQuitText(1);
}

WinScreen::WinDecision WinScreen::getWinDecision()
{
    if(flagLeftOption)
        return WinDecision::CONTINUE;
    return WinDecision::QUIT;
}
