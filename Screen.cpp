#include "Screen.hpp"

const cv::Scalar WinScreen::COLOR {CV_RGB(30,150,30)};
const cv::Scalar WinScreen::FONT_COLOR {CV_RGB(0,0,0)};

WinScreen::WinScreen()
{
    image = cv::Mat{HEIGHT, WIDTH, CV_8UC3, COLOR}; 
    addBorder();

    const int big_font = 2;
    const int small_font = 1;

    const std::string win_s {"You win!"};
    const auto win_size = getTextSize(win_s, big_font);
    const auto win_position = cv::Point(
            (WIDTH - win_size.width) / 2, (HEIGHT + win_size.height) / 3);
    addText(win_s, win_position, big_font); 

    const std::string continue_s {"Continue"};
    const auto continue_size = getTextSize(continue_s, small_font);
    const auto continue_position = cv::Point(
            (WIDTH - continue_size.width) / 4, (HEIGHT + continue_size.height) * 2/3);
    addText(continue_s, continue_position, small_font); 

    const std::string quit_s {"Quit"};
    const auto quit_size = getTextSize(quit_s, small_font);
    const auto quit_position = cv::Point(
            (WIDTH - quit_size.width) * 3/4, (HEIGHT + quit_size.height) * 2/3);
    addText(quit_s, quit_position, small_font); 
}

void WinScreen::addBorder()
{
    cv::rectangle(image,
                  cv::Point(0,0),
                  cv::Point(WIDTH, HEIGHT),
                  CV_RGB(100, 20, 200),
                  10); //thickness
}

cv::Size WinScreen::getTextSize(const std::string& text, float font_scale)
{
    int baseline {0};
    return cv::getTextSize(text,
                           FONT_FACE, font_scale, FONT_THICKNESS,
                           &baseline);
}

void WinScreen::addText(const std::string& text, const cv::Point& position, float font_scale)
{
    cv::putText(image,
                text,
                position,
                FONT_FACE, font_scale, FONT_COLOR, FONT_THICKNESS * font_scale);
}

WinScreen::WinDecision WinScreen::getWinDecision()
{
    if(flagLeftOption)
        return WinDecision::CONTINUE;
    return WinDecision::QUIT;
}
