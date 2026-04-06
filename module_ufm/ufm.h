#include "../utils/config.h"
#include <opencv2/opencv.hpp>

class OpticalFlowUFM {
    public:
        OpticalFlowUFM(const ufm_config& cfg);  

        void process(const cv::Mat& frame);
        const cv::Mat& getFlow() const; 

    private:
        void preprocess(const cv::Mat& frame);
        void computeFlow();
        void postprocess(); 

    private:
        ufm_config config;  

        cv::Mat frame_curr;
        cv::Mat gray_curr;
        cv::Mat gray_prev;  

        cv::Mat flow_raw;
        cv::Mat flow_filtered;  

        cv::Rect roi;
        cv::Point roi_offset;   

        bool initialized = false;
};