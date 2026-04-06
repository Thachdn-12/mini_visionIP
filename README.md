# Mini Vision Pipeline

This project implements a simple vision processing pipeline including:
- Input module (camera/video)
- ISP processing
- Optical Flow (UFM)
- Motion refinement (SMDPS)

## Project Structure
.
├── app/           # main application
├── module_input/  # camera/video input
├── module_isp/    # image processing
├── module_ufm/    # optical flow
├── module_smdps/  # motion refinement
└── output/        # results

## Build
make

## Run
make run

## Performance

- FPS: ~7 FPS (optimized later)
- ISP latency: 5ms
- Optical Flow latency: 12ms

## TODO

- [ ] Optimize FPS to 30
- [ ] SIMD optimization
- [ ] Hardware acceleration
+-------------------+
|   Camera / Video  |
+---------+---------+
          ↓
+-------------------+
|   ISP (Preprocess)|
+---------+---------+
          ↓
+-------------------+
| Frame(t-1), Frame |
+---------+---------+
          ↓
+-------------------+
|       UMF         |
| Optical Flow      |
+---------+---------+
          ↓
   Vector Field (vx, vy)
          ↓
+-------------------+
|      SMDPS        |
| Flow Refinement   |
+---------+---------+
          ↓
+-------------------+
|     SMDPOST       |
| Motion Analysis   |
+---------+---------+
          ↓
+-------------------+
| Motion / Tracking |
+-------------------+