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
    // convert to grayscale
    cv::cvtColor(frame, gray_curr, cv::COLOR_BGR2GRAY);

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

    output.curr_gray = gray_curr;
    output.roi = roi;
    output.roi_offset = roi_offset;
}

/**
 *  Stage 2 – Compute Flow
 *  Dense Optical Flow - Farneback
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
    if (flow_filtered.empty())
        flow_filtered = flow_raw.clone();
    else
        flow_raw.copyTo(flow_filtered);

    for (int y = 0; y < flow_filtered.rows; y++) {
        for (int x = 0; x < flow_filtered.cols; x++) {
            cv::Vec2f& f = flow_filtered.at<cv::Vec2f>(y, x);

            float mag = std::sqrt(f[0]*f[0] + f[1]*f[1]);

            if (mag < config.flow_threshold) { // threshold
                f[0] = 0;
                f[1] = 0;
            }
        }
    }

    output.flow = flow_filtered;
    output.prev_gray = gray_prev;
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

cv::Point OpticalFlowUFM::getRoiOffset() const {
    return roi_offset;
}
/**
 *  Output getter
 */
const cv::Mat& OpticalFlowUFM::getFlow() const {
    return flow_filtered;
}

const ufm_output_t& OpticalFlowUFM::getOutput() const {
    return output;
}