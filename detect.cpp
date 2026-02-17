#include "opencv2/opencv.hpp"
#include <iostream>

int main()
{
    cv::VideoCapture cap("C:\\Users\\name\\projects\\lanedetection\\road.mp4");
    if (!cap.isOpened())
    {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }
    while (1)
    {
        cv::Mat frame, gray, blurredImage, edges, cdstp, maskedEdges;
        cap >> frame;

        if (frame.empty())
        {
            break;
        }
        imshow("Frame", frame);

        cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        imshow("GrayScale", gray);

        cv::GaussianBlur(gray, blurredImage, cv::Size(9, 9), 1.0);
        imshow("Blurred Image", blurredImage);

        cv::Canny(blurredImage, edges, 100, 120);
        imshow("Canny edge detection", edges);

        cv::Mat mask = cv::Mat::zeros(edges.size(), edges.type());

        int width = edges.cols;
        int height = edges.rows;

        int bottom_width_offset = 150;  
        int top_width_offset = 400;    
        int top_height = height * 0.53; 

        std::vector<cv::Point> roiPoints;
        roiPoints.push_back(cv::Point(bottom_width_offset, height));
        roiPoints.push_back(cv::Point(width - bottom_width_offset, height));
        roiPoints.push_back(cv::Point(width - top_width_offset, top_height));
        roiPoints.push_back(cv::Point(top_width_offset, top_height));

        cv::fillConvexPoly(mask, roiPoints, 255);

        cv::bitwise_and(edges, mask, maskedEdges);

        cdstp = frame.clone();
        std::vector<cv::Vec4i> linesP;
        cv::HoughLinesP(maskedEdges, linesP, 1, CV_PI / 180, 50, 50, 10);

        for (size_t i = 0; i < linesP.size(); i++)
        {
            cv::Vec4i l = linesP[i];
            cv::line(cdstp, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
        }
        imshow("Hough lines used probabilistic", cdstp);

        char c = (char)cv::waitKey(25);
        if (c == 27)
        {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}