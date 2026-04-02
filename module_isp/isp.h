#ifndef ISP_H
#define ISP_H

#include "../types.h"

bool isp_init();
bool isp_process(frame_t &in, frame_t &out);
void isp_release();

#endif