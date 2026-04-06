#pragma once
#include <opencv2/opencv.hpp>

inline cv::Mat drawFlow(const cv::Mat& flow) {
    cv::Mat flow_xy[2];
    cv::split(flow, flow_xy);

    cv::Mat magnitude, angle;
    cv::cartToPolar(flow_xy[0], flow_xy[1], magnitude, angle, true);

    cv::Mat hsv[3];

    hsv[0] = angle * 0.5;
    cv::normalize(magnitude, magnitude, 0, 255, cv::NORM_MINMAX);

    hsv[1] = cv::Mat::ones(angle.size(), CV_32F) * 255;
    hsv[2] = magnitude;

    cv::Mat hsv_merge, bgr;
    cv::merge(hsv, 3, hsv_merge);
    hsv_merge.convertTo(hsv_merge, CV_8U);

    cv::cvtColor(hsv_merge, bgr, cv::COLOR_HSV2BGR);

    return bgr;
}