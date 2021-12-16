#pragma once
#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

namespace graphics
{
    constexpr int    FONT_FACE {cv::FONT_HERSHEY_DUPLEX};
    constexpr int    FONT_THICKNESS {2};
    const cv::Scalar FONT_COLOR = CV_RGB(0,0,0);
    const cv::Scalar BORDER_COLOR = CV_RGB(200,100,20);
    constexpr int BORDER_THICKNESS {10};

    cv::Mat getColoredRectangleWithCenteredText(int height,
                                                int width,
                                                cv::Scalar color,
                                                const std::string& text,
                                                float fontScale = 1.0);
    cv::Mat getColoredRectangleWithCenteredText(cv::Scalar color,
                                                const std::string& text,
                                                float fontScale = 1.0);
    void addBorder(cv::Mat& image, cv::Scalar borderColor = BORDER_COLOR);
    void pasteRectangleOntoImage(const cv::Mat& rectangle,
                                 cv::Mat& image,
                                 const cv::Point& origin);
    void pasteRectangleOntoImageCentered(const cv::Mat& rectangle,
                                         cv::Mat& image);
}

