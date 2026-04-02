#include "isp.h"
#include <opencv2/opencv.hpp>

static cv::Mat gray, blur_img, resized;

bool isp_init()
{
    return true;
}

bool isp_process(frame_t &in, frame_t &out)
{
    cv::Mat input(in.height, in.width, 
                  in.channels == 3 ? CV_8UC3 : CV_8UC1,
                  in.data);

    // 1. Convert to grayscale
    if (in.channels == 3)
        cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    else
        gray = input;

    // 2. Noise reduction
    cv::GaussianBlur(gray, blur_img, cv::Size(5,5), 0);

    // 3. Resize
    cv::resize(blur_img, resized, cv::Size(640, 480));

    // Output
    out.data = resized.data;
    out.width = resized.cols;
    out.height = resized.rows;
    out.channels = 1;
    out.timestamp = in.timestamp;

    return true;
}

void isp_release()
{
}