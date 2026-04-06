#include "../utils/config.h"
#include <opencv2/opencv.hpp>
#include "ufm_types.h"

class OpticalFlowUFM {
    public:
        OpticalFlowUFM(const ufm_config& cfg);  

        void process(const cv::Mat& frame);
        cv::Point getRoiOffset() const;
        const cv::Mat& getFlow() const; 
        const ufm_output_t& getOutput() const; 

    private:
        void preprocess(const cv::Mat& frame);
        void computeFlow();
        void postprocess(); 

    private:
        ufm_config config;  
        ufm_output_t output;

        cv::Mat frame_curr;
        cv::Mat frame_prev;
        cv::Mat gray_curr;
        cv::Mat gray_prev;  

        cv::Mat flow_raw;
        cv::Mat flow_filtered;  

        cv::Rect roi;
        cv::Point roi_offset;   

        bool initialized = false;
};