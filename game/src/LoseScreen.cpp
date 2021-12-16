#include "LoseScreen.hpp"

LoseScreen::LoseScreen()
{
    image = cv::Mat{HEIGHT, WIDTH, CV_8UC3, COLOR}; 
    graphics::addBorder(image);

    addLoseText();
    addOkText();
}

void LoseScreen::addLoseText()
{
    const auto loseFontScale = 2.0;
    cv::Mat textBox = graphics::getColoredRectangleWithCenteredText(
                COLOR, "You lose :(", loseFontScale);
    const auto origin = cv::Point(
            (WIDTH - textBox.cols) / 2, (HEIGHT + textBox.rows) / 3);
    graphics::pasteRectangleOntoImage(textBox, image, origin);
}

void LoseScreen::addOkText()
{
    cv::Mat textBox = graphics::getColoredRectangleWithCenteredText(COLOR, "OK");
    const auto origin = cv::Point(
            (WIDTH - textBox.cols) / 2, (HEIGHT + textBox.rows) * 2/3);
    graphics::pasteRectangleOntoImage(textBox, image, origin);
}

