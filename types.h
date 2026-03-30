#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

typedef struct {
    uint8_t *data;
    int width;
    int height;
    int channels;   // 1 = gray, 3 = RGB
    uint64_t timestamp;
} frame_t;

#endif