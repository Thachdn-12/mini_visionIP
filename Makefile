# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# OpenCV (auto detect bằng pkg-config)
OPENCV_FLAGS = `pkg-config --cflags --libs opencv4`

# Source files
SRC = app/main.cpp \
      module_input/input.cpp \
      module_isp/isp.cpp \
	  module_ufm/ufm.cpp

# Output binary
TARGET = ouput_video

# Default target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(OPENCV_FLAGS)

# Run app (camera)
run: $(TARGET)
	./$(TARGET)

# Run với video file
run_video: $(TARGET)
	./$(TARGET) video.mp4

# Clean build
clean:
	rm -f $(TARGET)