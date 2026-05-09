# Mini Vision Pipeline

A lightweight modular computer vision pipeline written in C/C++ for experimenting with ISP preprocessing, optical flow estimation, and motion analysis.

This project is designed as a learning-oriented vision framework that simulates the architecture of a real embedded vision system or ISP pipeline.

---

# Features

- Modular vision processing pipeline
- Camera / video frame input support
- Basic ISP preprocessing stage
- Optical flow estimation
- Motion refinement and analysis
- Simple Makefile-based build system
- Lightweight and easy to extend

---

# Pipeline Overview

```text
+-------------------+
| Camera / Video    |
+---------+---------+
          |
          v
+-------------------+
| Input Module      |
| Frame Acquisition |
+---------+---------+
          |
          v
+-------------------+
| ISP Module        |
| Preprocessing     |
+---------+---------+
          |
          v
+-------------------+
| UFM Module        |
| Optical Flow      |
+---------+---------+
          |
          v
+-------------------+
| SMDPS Module      |
| Motion Refinement |
+---------+---------+
          |
          v
+-------------------+
| Motion Analysis   |
| Tracking / Output |
+-------------------+
```

---

# Project Structure

```text
mini_visionIP/
│
├── app/                 # Main application
├── module_input/        # Camera / video input module
├── module_isp/          # ISP preprocessing module
├── module_ufm/          # Optical flow module
├── utils/               # Shared utilities
├── Makefile             # Build system
├── main.cpp             # Entry point
├── types.h              # Shared data types
└── README.md
```

---

# Modules

## Input Module

Responsible for:

- Capturing frames from camera or video source
- Frame buffering
- Providing input data for downstream modules

---

## ISP Module

The ISP (Image Signal Processing) stage performs preprocessing operations before motion estimation.

Typical tasks:

- Color conversion
- Noise reduction
- Frame normalization
- Basic image enhancement

This stage simulates the behavior of a simplified embedded ISP pipeline.

---

## UFM Module

The UFM module computes optical flow between consecutive frames.

Output:

```text
(vx, vy)
```

Where:

- `vx` = horizontal motion vector
- `vy` = vertical motion vector

Used for:

- Motion estimation
- Object movement detection
- Frame-to-frame tracking

---

## Motion Refinement

Post-processing stage used to refine motion vectors and reduce noisy flow data.

Possible future improvements:

- Temporal filtering
- Confidence estimation
- Motion clustering
- Region tracking

---

# Build Instructions

## Requirements

- Linux environment
- GCC / G++
- Make

## Build

```bash
make
```

---

# Run

```bash
make run
```

---

# Performance

Current prototype performance:

| Metric | Value |
|---|---|
| FPS | ~7 FPS |
| ISP Latency | ~5 ms |
| Optical Flow Latency | ~12 ms |

---

# Future Improvements

- Optimize pipeline to reach 30 FPS
- SIMD optimization
- Multi-threaded processing
- Hardware acceleration
- GPU/NPU integration
- Better motion refinement algorithms
- Real-time camera support
- Embedded Linux deployment

---

# Example Use Cases

- Embedded vision research
- Drone motion tracking
- Smart camera prototypes
- Optical flow experimentation
- Educational computer vision projects

---

# Author

Developed by Do Ngoc Thach.

