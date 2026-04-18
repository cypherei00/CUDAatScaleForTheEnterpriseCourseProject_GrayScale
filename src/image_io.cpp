#include "image_io.h"

cv::Mat loadImage(const std::string& path) {
    return cv::imread(path, cv::IMREAD_COLOR);
}

void saveImage(const std::string& path, const cv::Mat& image) {
    cv::imwrite(path, image);
}