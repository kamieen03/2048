#include "WinScreen.hpp"

WinScreen::WinScreen()
{
    image = cv::Mat{HEIGHT, WIDTH, CV_8UC3, COLOR}; 
    graphics::addBorder(image);

    addWinText();
    drawDecisionPart(); 
}

void WinScreen::addWinText()
{
    const auto winFontScale = 2.0;
    cv::Mat textBox = graphics::getColoredRectangleWithCenteredText(
                COLOR, "You win!", winFontScale);
    const auto origin = cv::Point(
            (WIDTH - textBox.cols) / 2, (HEIGHT + textBox.rows) / 4);
    graphics::pasteRectangleOntoImage(textBox, image, origin);
}

void WinScreen::drawDecisionPart()
{
    addContinueText();
    addQuitText();
}

void WinScreen::addContinueText()
{
    const auto color = flagLeftOption ? OPTION_BACKGROUND : COLOR;
    cv::Mat textBox = graphics::getColoredRectangleWithCenteredText(color, "Continue");
    const auto origin = cv::Point(
            (WIDTH - textBox.cols) / 4, (HEIGHT + textBox.rows) * 3/5);
    graphics::pasteRectangleOntoImage(textBox, image, origin);
}

void WinScreen::addQuitText()
{
    const auto color = flagLeftOption ? COLOR : OPTION_BACKGROUND;
    cv::Mat textBox = graphics::getColoredRectangleWithCenteredText(color, "Quit");
    const auto origin = cv::Point(
            (WIDTH - textBox.cols) * 3/4, (HEIGHT + textBox.rows) * 3/5);
    graphics::pasteRectangleOntoImage(textBox, image, origin);
}

void WinScreen::setLeftOption()
{
    flagLeftOption = true;
    drawDecisionPart();
}

void WinScreen::setRightOption()
{
    flagLeftOption = false;
    drawDecisionPart();
}

CQDecision WinScreen::getWinDecision()
{
    if(flagLeftOption)
        return CQDecision::CONTINUE;
    return CQDecision::QUIT;
}

