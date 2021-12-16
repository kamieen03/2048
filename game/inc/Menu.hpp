#include <optional>
#include <vector>
#include <map>
#include <cassert>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>

#include "KeyHandler.hpp"
#include "graphics.hpp"
#include "CQDecision.hpp"
#include "ColorSchemeReader.hpp"

using Key = KeyHandler::Key;

class Menu
{
public:
    struct SignalSet
    {
        bool changedColorScheme;
        std::optional<CQDecision> cqDecision;
        SignalSet();
    };

    Menu(const std::vector<ColorScheme>& colorSchemes);
    const ColorScheme& getActiveScheme() const;
    cv::Mat getImage() const {return drawer.getImage();}
    SignalSet handleKey(Key key);

private:
    class RotationalIdx
    {
    public:
        RotationalIdx(int numStates);
        int getValue() const {return idx;}
        RotationalIdx& operator++();
        RotationalIdx& operator--();
    private:
        int idx {0};
        const int numStates;
    };

    class BoundedIdx
    {
    public:
        BoundedIdx(int max);
        int getValue() const {return idx;}
        BoundedIdx& operator++();
        BoundedIdx& operator--();
    private:
        int idx {0};
        static constexpr int min {0};
        const int max;
    };
    friend bool operator==(const BoundedIdx& lhs, int rhs);

    enum Option : int
    {
        ChangeColorScheme = 0,
        Continue = 1,
        Quit = 2
    };

    class MenuDrawer
    {
    public:
        cv::Mat getImage() const {return image;}
        void draw(const std::map<Menu::Option, std::string>& optionTextMapForDrawer,
                  const BoundedIdx& highlightIdx);

        static constexpr int HEIGHT {500};
        static constexpr int WIDTH  {300};
        static const cv::Scalar COLOR;
        static const cv::Scalar FRAME_COLOR;
        static constexpr int BOX_HEIGHT {70};
        static constexpr int BOX_WIDTH  {WIDTH*2/3};
        static const cv::Scalar BOX_COLOR;
        static const cv::Scalar BOX_FRAME_COLOR;

    private:
        void drawOptionBox(const std::string& text, int distanceFromTheTop, bool highlight);

        cv::Mat image {HEIGHT, WIDTH, CV_8UC3, COLOR};
    };

    void tryMoveUp();
    void tryMoveDown();
    bool tryMoveLeft();
    bool tryMoveRight();
    std::optional<CQDecision> tryConfirmOption();
    auto getMapForDrawer() const;
    void draw();

    MenuDrawer drawer;
    const std::vector<ColorScheme>& colorSchemes;
    RotationalIdx colorSchemeIdx;
    BoundedIdx optionIdx {2};
};

