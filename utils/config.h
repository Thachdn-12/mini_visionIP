#ifndef CONFIG_H
#define CONFIG_H
#include <opencv2/opencv.hpp>

struct isp_config_t {
    bool enable_blur;
    int out_width;
    int out_height;
};

struct ufm_config {
    // ROI
    bool use_roi = false;
    cv::Rect roi = {0, 0, 0, 0};

    // Downsample
    bool use_downsample = true;
    float scale = 0.5f;

    // Threshold flow
    float flow_threshold = 1.0f;

    // Blur
    bool use_blur = true;
};

struct SMDPSConfig {
    float thresh_mag = 2.0f;
    int radius = 2;
    float sigma_s = 5.0f;
    float sigma_c = 10.0f;
};

#endif