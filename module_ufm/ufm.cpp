#include <iostream>
#include <opencv2/opencv.hpp>
#include "../utils/config.h"
#include "ufm.h"

OpticalFlowUFM::OpticalFlowUFM(const ufm_config& cfg) {
   config = cfg;
}

/**
 *  Stage 1 – Preprocess
 */
void OpticalFlowUFM::preprocess(const cv::Mat& frame) {
    frame_curr = frame.clone();

    // convert to grayscale
    cv::cvtColor(frame_curr, gray_curr, cv::COLOR_BGR2GRAY);

    // Downsample
    if(config.use_downsample) {
        cv::resize(gray_curr, gray_curr, cv::Size(), 
                   config.scale, config.scale);
    }
    // ROI
    if (config.use_roi) {
        float s = config.use_downsample ? config.scale : 1.0f;

        cv::Rect r(
            config.roi.x * s,
            config.roi.y * s,
            config.roi.width * s,
            config.roi.height * s
        );
        // clamp
        r &= cv::Rect(0, 0, gray_curr.cols, gray_curr.rows);

        if (r.width > 0 && r.height > 0) {
            roi = r;
            roi_offset = r.tl();
            gray_curr = gray_curr(r).clone();
        }
    }

    // Blur reduce noise
    if (config.use_blur) {
        cv::GaussianBlur(gray_curr, gray_curr, cv::Size(5,5), 0);
    }
}

/**
 *  Stage 2 – Compute Flow
 */
void OpticalFlowUFM::computeFlow() {
    cv::calcOpticalFlowFarneback(
        gray_prev,
        gray_curr,
        flow_raw,
        0.5,
        3,
        15,
        3,
        5,
        1.2,
        0
    );
}

/**
 *  Stage 3 – Postprocess
 */
void OpticalFlowUFM::postprocess() {
    // filter noise: threshold magnitude
    flow_filtered = flow_raw.clone();

    for (int y = 0; y < flow_filtered.rows; y++) {
        for (int x = 0; x < flow_filtered.cols; x++) {
            cv::Vec2f& f = flow_filtered.at<cv::Vec2f>(y, x);

            float mag = std::sqrt(f[0]*f[0] + f[1]*f[1]);

            if (mag < 1.0f) { // threshold
                f[0] = 0;
                f[1] = 0;
            }
        }
    }
}

void OpticalFlowUFM::process(const cv::Mat& frame) {
    preprocess(frame);

    if (!initialized) {
        gray_prev = gray_curr.clone();
        initialized = true;
        return;
    }

    computeFlow();
    postprocess();

    // update buffer 
    gray_prev = gray_curr.clone();
}

/**
 *  Output getter
 */
const cv::Mat& OpticalFlowUFM::getFlow() const {
    return flow_filtered;
}