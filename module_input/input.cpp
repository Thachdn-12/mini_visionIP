#include "input.h"
#include <opencv2/opencv.hpp>

static cv::VideoCapture cap;
static cv::Mat frame_cv;

bool input_init(int cam_id)
{
    cap.open(cam_id);
    return cap.isOpened();
}

bool input_get_frame(frame_t &frame)
{
    if (!cap.read(frame_cv))
        return false;

    frame.data = frame_cv.data;
    frame.width = frame_cv.cols;
    frame.height = frame_cv.rows;
    frame.channels = frame_cv.channels();
    frame.timestamp = cv::getTickCount();

    return true;
}

void input_release()
{
    cap.release();
}
