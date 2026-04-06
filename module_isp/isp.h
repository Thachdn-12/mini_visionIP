#ifndef ISP_H
#define ISP_H

#include "../types.h"
#include "../utils/config.h"

bool isp_init(const isp_config_t& cfg);
bool isp_process(frame_t &in, frame_t &out);
void isp_release();

#endif