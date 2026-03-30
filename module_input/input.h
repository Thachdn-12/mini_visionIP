#ifndef INPUT_H
#define INPUT_H

#include "../types.h"

bool input_init(int cam_id);
bool input_get_frame(frame_t &frame);
void input_release();

#endif