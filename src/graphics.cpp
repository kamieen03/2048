#include "graphics.hpp"

namespace
{
    cv::Size getTextSize(const std::string& text, float fontScale)
    {
        int baseline {0};
        return cv::getTextSize(text,
                               graphics::FONT_FACE,
                               fontScale,
                               graphics::FONT_THICKNESS,
                               &baseline);
    }
}

namespace graphics
{
    cv::Mat getColoredRectangleWithCenteredText(int height,
                                                int width,
                                                cv::Scalar color,
                                                const std::string& text,
                                                float fontScale)
    {
        cv::Mat img{height, width, CV_8UC3, color};
        const auto size = getTextSize(text, fontScale);
        const auto pos = cv::Point((width - size.width) / 2, (height + size.height) / 2);
        cv::putText(img, text, pos, FONT_FACE, fontScale, FONT_COLOR, FONT_THICKNESS * fontScale);
        return img;
    }

    cv::Mat getColoredRectangleWithCenteredText(cv::Scalar color,
                                                const std::string& text,
                                                float fontScale)
    {
        const auto size = getTextSize(text, fontScale);
        return getColoredRectangleWithCenteredText(
                size.height+12, size.width+12, color, text, fontScale);
    }

    void addBorder(cv::Mat& image, cv::Scalar borderColor)
    {
        cv::rectangle(image,
                      cv::Point(0,0),
                      cv::Point(image.cols, image.rows),
                      borderColor,
                      BORDER_THICKNESS); //thickness
    }


    void pasteRectangleOntoImage(const cv::Mat& rectangle,
                                 cv::Mat& image,
                                 const cv::Point& origin)
    {
        const cv::Size size(rectangle.cols, rectangle.rows);
        auto dst = image(cv::Rect(origin, size));
        rectangle.copyTo(dst);
    }

    void pasteRectangleOntoImageCentered(const cv::Mat& rectangle,
                                         cv::Mat& image)
    {
        const auto w = (image.cols - rectangle.cols) / 2;
        const auto h = (image.rows - rectangle.rows) / 2;
        const cv::Point origin(w, h);
        pasteRectangleOntoImage(rectangle, image, origin);
    }
}

