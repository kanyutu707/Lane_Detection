# Lane Detection using OpenCV (C++ & CMake)

This project implements a classical computer vision pipeline for lane detection using C++ and OpenCV. It processes a road video, detects lane markings using edge detection and the Probabilistic Hough Transform, and overlays detected lane lines onto the original frames.

Repository: [https://github.com/kanyutu707/Lane_Detection](https://github.com/kanyutu707/Lane_Detection)

---

## Overview

The purpose of this project is to demonstrate a traditional (non–deep learning) approach to lane detection using fundamental image processing techniques. The implementation is lightweight, easy to understand, and ideal for learning core computer vision concepts.

### Processing Pipeline

* Video frame capture
* Grayscale conversion
* Gaussian blurring
* Canny edge detection
* Region of Interest (ROI) masking
* Probabilistic Hough Line Transform
* Visualization of intermediate and final results

---

## Important: Use Your Own Video

The current code contains a hard-coded video path:

```cpp
cv::VideoCapture cap("C:\\Users\\name\\projects\\lanedetection\\road.mp4");
```

Before running the project, replace this path with the location of a road video on your system:

```cpp
cv::VideoCapture cap("path_to_your_video.mp4");
```

Make sure:

* The file exists.
* The path is correct.
* The video clearly shows visible lane markings.

Alternatively, place your video inside the project directory:

```cpp
cv::VideoCapture cap("road.mp4");
```

---

## How the Algorithm Works

### 1. Grayscale Conversion

```cpp
cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
```

Reduces computational complexity and prepares the frame for edge detection.

---

### 2. Gaussian Blur

```cpp
cv::GaussianBlur(gray, blurredImage, cv::Size(9, 9), 1.0);
```

Reduces noise and improves edge stability.

---

### 3. Canny Edge Detection

```cpp
cv::Canny(blurredImage, edges, 100, 120);
```

Thresholds:

* Lower: 100
* Upper: 120

These may require tuning depending on lighting conditions.

---

### 4. Region of Interest (ROI)

```cpp
cv::fillConvexPoly(mask, roiPoints, 255);
cv::bitwise_and(edges, mask, maskedEdges);
```

A trapezoidal mask isolates the road region to eliminate irrelevant edges.

---

### 5. Probabilistic Hough Line Transform

```cpp
cv::HoughLinesP(maskedEdges, linesP, 1, CV_PI / 180, 50, 50, 10);
```

Parameters:

* Rho resolution: 1 pixel
* Theta resolution: 1°
* Threshold: 50
* Minimum line length: 50
* Maximum line gap: 10

Detected lines are drawn onto the original frame.

---

## Requirements

* C++11 or later
* CMake (3.10 or later recommended)
* OpenCV 4.x
* Windows, Linux, or macOS

---

# Build Instructions (Using CMake)

## 1. Clone the Repository

```bash
git clone https://github.com/kanyutu707/Lane_Detection.git
cd Lane_Detection
```

---

## 2. Create Build Directory

```bash
mkdir build
cd build
```

---

## 3. Run CMake

### Linux / macOS

```bash
cmake ..
```

If OpenCV is not automatically found:

```bash
cmake -DOpenCV_DIR=/path/to/opencv/build ..
```

---

### Windows (Visual Studio)

```bash
cmake .. -G "Visual Studio 17 2022"
```

Then open the generated `.sln` file in Visual Studio and build.

---

## 4. Build

### Linux / macOS

```bash
make
```

### Windows

Build from Visual Studio or:

```bash
cmake --build . --config Release
```

---

## 5. Run

```bash
./lane_detection
```

(Windows: `lane_detection.exe`)

---

## Limitations

* Works best with clear, straight lane markings
* Sensitive to lighting changes
* Struggles with curved lanes
* No temporal smoothing between frames
* Fixed thresholds may not generalize well

---

## Possible Improvements

* Adaptive Canny thresholds
* Lane line averaging and temporal smoothing
* Real-time webcam input
* Polynomial fitting for curved lanes
* Perspective transformation (bird’s-eye view)
* Integration with deep learning approaches

---

## License

Open-source for educational and research purposes.

---

## Author

Kanyutu
GitHub: [https://github.com/kanyutu707](https://github.com/kanyutu707)

---

