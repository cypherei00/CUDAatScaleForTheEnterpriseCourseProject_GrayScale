#include <iostream>
#include <filesystem>
#include <vector>
#include <chrono>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <npp.h>
#include <cuda_runtime.h>

#include "image_io.h"

namespace fs = std::filesystem;

void checkCuda(cudaError_t err) {
    if (err != cudaSuccess) {
        std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
        exit(1);
    }
}

int main(int argc, char* argv[]) {

    std::string inputFolder = "data/input";
    std::string outputFolder = "data/output";
    
    std::ofstream logFile(outputFolder + "/log.txt");
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file\n";
        return 1;
    }
    std::vector<std::string> files;
    for (const auto& entry : fs::directory_iterator(inputFolder)) {
        files.push_back(entry.path().string());
    }

    std::cout << "Found " << files.size() << " images.\n";

    auto start = std::chrono::high_resolution_clock::now();

    for (const auto& file : files) {
        cv::Mat img = loadImage(file);
        if (img.empty()) continue;
        
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
        // Convert to grayscale using NPP
        int width = img.cols;
        int height = img.rows;

        NppiSize size = { width, height };

        unsigned char* d_src;
        unsigned char* d_dst;

        size_t srcSize = width * height * 3;
        size_t dstSize = width * height;

        checkCuda(cudaMalloc(&d_src, srcSize));
        checkCuda(cudaMalloc(&d_dst, dstSize));

        checkCuda(cudaMemcpy(d_src, img.data, srcSize, cudaMemcpyHostToDevice));

        // GPU grayscale conversion (NPP)
        nppiRGBToGray_8u_C3C1R(
            d_src,
            width * 3,
            d_dst,
            width,
            size
        );

        cv::Mat gray(height, width, CV_8UC1);

        checkCuda(cudaMemcpy(gray.data, d_dst, dstSize, cudaMemcpyDeviceToHost));

        std::string filename = fs::path(file).filename().string();
        saveImage(outputFolder + "/" + filename, gray);
        logFile << filename << " processed\n";

        cudaFree(d_src);
        cudaFree(d_dst);
    }

    
    logFile.close();
    return 0;
}