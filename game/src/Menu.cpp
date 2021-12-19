#include "Menu.hpp"
#include <iostream>

Menu::SignalSet::SignalSet()
    : changedColorScheme(false),
      cqDecision(std::nullopt)
{}

Menu::Menu(const std::vector<ColorScheme>& colorSchemes)
    : colorSchemes(colorSchemes),
      colorSchemeIdx(colorSchemes.size())
{
    draw();
}

const ColorScheme& Menu::getActiveScheme() const
{
    return colorSchemes[colorSchemeIdx.getValue()];
}

Menu::SignalSet Menu::handleKey(Key key)
{
    Menu::SignalSet ss;
    switch(key)
    {
        case Key::UP:
            tryMoveUp();
            break;
        case Key::DOWN:
            tryMoveDown();
            break;
        case Key::LEFT:
            ss.changedColorScheme = tryMoveLeft();
            break;
        case Key::RIGHT:
            ss.changedColorScheme = tryMoveRight();
            break;
        case Key::ENTER:
            ss.cqDecision = tryConfirmOption();
            break;
        case Key::QUIT:
            ss.cqDecision = CQDecision::CONTINUE;
            break;
    }
    draw();
    return ss;
}

void Menu::tryMoveUp()
{
    --optionIdx;
}

void Menu::tryMoveDown()
{
    ++optionIdx;
}

bool Menu::tryMoveLeft()
{
    if(optionIdx == Option::ChangeColorScheme)
    {
        --colorSchemeIdx;
        return true;
    }
    return false;
}

bool Menu::tryMoveRight()
{
    if(optionIdx == Option::ChangeColorScheme)
    {
        ++colorSchemeIdx;
        return true;
    }
    return false;
}

std::optional<CQDecision> Menu::tryConfirmOption()
{
    if(optionIdx == Option::Continue)
    {
        return CQDecision::CONTINUE;
    }
    else if(optionIdx == Option::Quit)
    {
        return CQDecision::QUIT;
    }
    return std::nullopt;
}

auto Menu::getMapForDrawer() const
{
    std::map<Option, std::string> optionTextMapForDrawer;
    optionTextMapForDrawer[Option::ChangeColorScheme] =
        getActiveScheme().getName();
    optionTextMapForDrawer[Option::Continue] = "Continue";
    optionTextMapForDrawer[Option::Quit] = "Quit";
    return optionTextMapForDrawer;
}

void Menu::draw()
{
    const auto map = getMapForDrawer();
    drawer.draw(map, optionIdx);
}





const cv::Scalar Menu::MenuDrawer::COLOR = CV_RGB(198, 218, 191);
const cv::Scalar Menu::MenuDrawer::BOX_COLOR = CV_RGB(136, 212, 152);
const cv::Scalar Menu::MenuDrawer::FRAME_COLOR = CV_RGB(17, 75, 95);
const cv::Scalar Menu::MenuDrawer::BOX_FRAME_COLOR = CV_RGB(26, 147, 111);

void Menu::MenuDrawer::draw(const std::map<Menu::Option, std::string>& optionTextMapForDrawer,
                            const BoundedIdx& highlightIdx)
{
    assert(optionTextMapForDrawer.size() == 3);
    for(const auto& [option, text] : optionTextMapForDrawer)
    {
        drawOptionBox(text, 20 * (option+1) + BOX_HEIGHT * option, highlightIdx == option);
    }
    graphics::addBorder(image, FRAME_COLOR);
}

void Menu::MenuDrawer::drawOptionBox(const std::string& text, int distanceFromTheTop, bool highlight)
{
    auto box = graphics::getColoredRectangleWithCenteredText(
        BOX_HEIGHT, BOX_WIDTH, BOX_COLOR, text);
    if(highlight)
    {
        graphics::addBorder(box, BOX_FRAME_COLOR);
    }
    constexpr auto w = (WIDTH - BOX_WIDTH) / 2;
    const cv::Point origin(w, distanceFromTheTop);
    graphics::pasteRectangleOntoImage(box, image, origin);
}

