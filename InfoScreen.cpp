#include "InfoScreen.hpp"

const cv::Scalar InfoScreen::FONT_COLOR {CV_RGB(0,0,0)};

void InfoScreen::addBorder(cv::Mat& image)
{
    cv::rectangle(image,
                  cv::Point(0,0),
                  cv::Point(WIDTH, HEIGHT),
                  CV_RGB(100, 20, 200),
                  10); //thickness
}

cv::Size InfoScreen::getTextSize(const std::string& text, float fontScale)
{
    int baseline {0};
    return cv::getTextSize(text,
                           FONT_FACE, fontScale, FONT_THICKNESS,
                           &baseline);
}

void InfoScreen::addText(cv::Mat& image, const std::string& text,
                         const cv::Point& position, float fontScale)
{
    cv::putText(image,
                text,
                position,
                FONT_FACE, fontScale, FONT_COLOR, FONT_THICKNESS * fontScale);
}






WinScreen::WinScreen()
{
    image = cv::Mat{HEIGHT, WIDTH, CV_8UC3, COLOR}; 
    addBorder(image);

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
    addText(image, text, pos, fontScale); 
}

void WinScreen::addContinueText(float fontScale)
{
    const std::string text {"Continue"};
    const auto size = getTextSize(text, fontScale);
    const auto pos = cv::Point(
            (WIDTH - size.width) / 4, (HEIGHT + size.height) * 2/3);
    addOptionBackgroudRectangle(pos, size, flagLeftOption);
    addText(image, text, pos, fontScale); 
}

void WinScreen::addQuitText(float fontScale)
{
    const std::string text {"Quit"};
    const auto size = getTextSize(text, fontScale);
    const auto pos = cv::Point(
            (WIDTH - size.width) * 3/4, (HEIGHT + size.height) * 2/3);
    addOptionBackgroudRectangle(pos, size, !flagLeftOption);
    addText(image, text, pos, fontScale); 
}

void WinScreen::addOptionBackgroudRectangle(cv::Point p1, const cv::Size& size, bool option)
{
    const auto color = option ? OPTION_BACKGROUND : COLOR;
    const auto p2 = p1 + cv::Point(size.width+6, -size.height-6);
    p1 += cv::Point(-6,6);
    cv::rectangle(image, p1, p2, color, cv::FILLED);
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





LoseScreen::LoseScreen()
{
    image = cv::Mat{HEIGHT, WIDTH, CV_8UC3, COLOR}; 
    addBorder(image);

    const int bigFont = 2;
    const int smallFont = 1;

    addLoseText(bigFont);
    addOkText(smallFont);
}

void LoseScreen::addLoseText(float fontScale)
{
    const std::string text {"You lose :("};
    const auto size = getTextSize(text, fontScale);
    const auto pos = cv::Point(
            (WIDTH - size.width) / 2, (HEIGHT + size.height) / 3);
    addText(image, text, pos, fontScale); 
}

void LoseScreen::addOkText(float fontScale)
{
    const std::string text {"OK"};
    const auto size = getTextSize(text, fontScale);
    const auto pos = cv::Point(
            (WIDTH - size.width) / 2, (HEIGHT + size.height) * 2/3);
    addText(image, text, pos, fontScale); 
}
