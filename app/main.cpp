#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <iomanip>

#include "../types.h"
#include "../module_input/input.h"
#include "../module_isp/isp.h"
#include "../module_ufm/ufm.h"
#include "../utils/config.h"

#define NOW std::chrono::high_resolution_clock::now()
#define MS(t) std::chrono::duration<double, std::milli>(t).count()

static int counter = 0;


int main()
{
    frame_t in_frame;
    frame_t out_frame;
    // ISP config
    isp_config_t isp_cfg;

    isp_cfg.enable_blur = true;
    isp_cfg.out_width = 640;
    isp_cfg.out_height = 480;

    // UFM config
    ufm_config ufm_cfg;

    ufm_cfg.use_roi = true;
    ufm_cfg.roi = cv::Rect(100, 100, 200, 200);
    ufm_cfg.use_downsample = true;
    ufm_cfg.scale = 0.5f;
    OpticalFlowUFM ufm(ufm_cfg);

    if (!input_init(0))
    {
        std::cerr << "Cannot open camera\n";
        return -1;
    }

    isp_init(isp_cfg);
    auto prev_time = std::chrono::high_resolution_clock::now();
    double fps = 0.0;
    while (true)
    {
        counter++;

        auto t0 = NOW;

        // ===== INPUT =====
        if (!input_get_frame(in_frame))
            break;

        auto t1 = NOW;

        // ===== ISP =====
        if (!isp_process(in_frame, out_frame))
            break;

        auto t2 = NOW;

        auto t3 = NOW;

        // ===== UFM =====
        cv::Mat isp_mat(out_frame.height, out_frame.width,
                        CV_8UC1, out_frame.data);
        
        // convert gray → BGR
        cv::Mat isp_bgr;
        cv::cvtColor(isp_mat, isp_bgr, cv::COLOR_GRAY2BGR);
        
        ufm.process(isp_bgr);
        auto flow = ufm.getFlow();
        
        auto t4 = NOW;

        // ===== FPS =====
        double total_dt = std::chrono::duration<double>(t2 - prev_time).count();
        prev_time = t2;

        double instant_fps = 1.0 / total_dt;
        double alpha = 0.9;
        fps = alpha * fps + (1 - alpha) * instant_fps;

        // ===== LATENCY =====
        double input_time   = MS(t1 - t0);
        double isp_time     = MS(t2 - t1);
        double total_time   = MS(t2 - t0);
        double ufm_time     = MS(t4 - t3);

        // ===== LOG =====
        if (counter % 10 == 0){
            std::cout << std::fixed << std::setprecision(2)
                << "Input: " << input_time << " ms | "
                << "ISP: "   << isp_time   << " ms | "
                << "UFM: "   << ufm_time   << " ms | "
                << "Total: " << total_time << " ms | "
                << "FPS: "   << fps
                << std::endl;
        }
        
        // ===== DISPLAY =====
        cv::Mat out(out_frame.height, out_frame.width,
                CV_8UC1, out_frame.data);

        cv::putText(out,
                "FPS: " + std::to_string((int)fps),
                cv::Point(20, 30),
                cv::FONT_HERSHEY_SIMPLEX,
                1.0,
                cv::Scalar(255),
                2);
        cv::imshow("ISP Output", out);

        int key = cv::waitKey(1);
        if (key == 'b')
        {
            isp_cfg.enable_blur = !isp_cfg.enable_blur;
            isp_init(isp_cfg);
        
            std::cout << "Blur: " << isp_cfg.enable_blur << std::endl;
        }
        if (key == 27) // ESC
            break;
    }


    input_release();
    isp_release();

    return 0;
}