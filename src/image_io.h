#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include <opencv2/opencv.hpp>
#include <string>

cv::Mat loadImage(const std::string& path);
void saveImage(const std::string& path, const cv::Mat& image);

#endif