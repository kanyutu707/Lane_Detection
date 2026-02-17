# Lane Detection using OpenCV (C++)

This project implements a classical computer vision pipeline for lane detection using C++ and OpenCV. It processes a road video, detects lane markings using edge detection and the Probabilistic Hough Transform, and overlays the detected lane lines onto the original frames.

Repository: [https://github.com/kanyutu707/Lane_Detection.git](https://github.com/kanyutu707/Lane_Detection.git)

---

## Overview

The purpose of this project is to demonstrate a traditional (non–deep learning) approach to lane detection using fundamental image processing techniques. The implementation is lightweight, easy to understand, and suitable for learning computer vision concepts.

The pipeline includes:

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

Before running the project, you must replace this path with the location of a road video on your own system.

Example:

```cpp
cv::VideoCapture cap("path_to_your_video.mp4");
```

Make sure:

* The file exists.
* The path is correct.
* The video clearly shows visible lane markings.

You may also place your video file inside the project directory and reference it directly:

```cpp
cv::VideoCapture cap("road.mp4");
```

---

## How the Algorithm Works

For each frame in the input video, the following steps are performed:

### 1. Grayscale Conversion

Each frame is converted from BGR to grayscale:

```cpp
cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
```

This reduces computational complexity and prepares the image for edge detection.

---

### 2. Gaussian Blur

Noise is reduced using a 9×9 Gaussian kernel:

```cpp
cv::GaussianBlur(gray, blurredImage, cv::Size(9, 9), 1.0);
```

This smooths the image and improves edge detection stability.

---

### 3. Canny Edge Detection

Edges are extracted using:

```cpp
cv::Canny(blurredImage, edges, 100, 120);
```

Thresholds:

* Lower threshold: 100
* Upper threshold: 120

These values may need adjustment depending on lighting conditions and video quality.

---

### 4. Region of Interest (ROI)

A trapezoidal mask is applied to isolate the road area where lanes are expected.

```cpp
cv::fillConvexPoly(mask, roiPoints, 255);
cv::bitwise_and(edges, mask, maskedEdges);
```

This step removes unnecessary edges from areas such as the sky or roadside objects.

---

### 5. Probabilistic Hough Line Transform

Lane lines are detected using:

```cpp
cv::HoughLinesP(maskedEdges, linesP, 1, CV_PI / 180, 50, 50, 10);
```

Parameters:

* Rho resolution: 1 pixel
* Theta resolution: 1 degree
* Threshold: 50
* Minimum line length: 50
* Maximum line gap: 10

Detected lines are drawn onto a copy of the original frame.

---

## Requirements

* C++ compiler (C++11 or later recommended)
* OpenCV (version 4.x recommended)
* Windows, Linux, or macOS

---

## Build Instructions

### Clone the Repository

```bash
git clone https://github.com/kanyutu707/Lane_Detection.git
cd Lane_Detection
```

### Compile (Linux/macOS)

```bash
g++ main.cpp -o lane_detection `pkg-config --cflags --libs opencv4`
```

### Compile (Windows with Visual Studio)

1. Install OpenCV.
2. Configure include directories.
3. Link OpenCV libraries in project settings.
4. Build and run.

---

## Limitations

* Works best with clear lane markings.
* Sensitive to lighting changes.
* Does not handle curved lanes robustly.
* No temporal smoothing between frames.
* Fixed thresholds may not generalize to all road conditions.

---

## Possible Improvements

* Adaptive Canny thresholds
* Lane line averaging and stabilization
* Real-time webcam input
* Curved lane fitting
* Perspective transformation (bird’s-eye view)
* Integration with machine learning approaches

---

## License

This project is open-source and available for educational and research purposes.

---

## Author

Kanyutu
GitHub: [https://github.com/kanyutu707](https://github.com/kanyutu707)

This project is intended for learning and experimentation with classical computer vision techniques for autonomous driving applications.
