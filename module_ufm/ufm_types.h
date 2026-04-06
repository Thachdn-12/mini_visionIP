#pragma once
#include <opencv2/opencv.hpp>

struct ufm_output_t {
    cv::Mat flow;        // optical flow (CV_32FC2)
    cv::Mat curr_gray;   // Current frame
    cv::Mat prev_gray;   // Previous frame

    cv::Rect roi;        // ROI 
    cv::Point roi_offset; // offset to map with global
};