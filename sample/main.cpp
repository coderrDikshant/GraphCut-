#include <iostream>
#include <opencv2/opencv.hpp>
#include "GraphCut.h"

// Safely convert seed mask to foreground/background points
void mask2Vec(const cv::Mat& img, std::vector<cv::Point>& fore, std::vector<cv::Point>& back) {
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            // Safe access using at<> instead of ptr<>
            cv::Vec3b pixel = img.at<cv::Vec3b>(y, x);
            if (pixel[2] >= 200)      // Red marks foreground
                fore.push_back(cv::Point(x, y));
            else if (pixel[1] >= 200) // Green marks background
                back.push_back(cv::Point(x, y));
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cout << "Usage: GraphCutter <input image> <input seed> <output path> <mask path>" << std::endl;
        return -1;
    }

    std::string inputPath = argv[1];
    std::string seedPath = argv[2];
    std::string outputPath = argv[3];
    std::string maskPath = argv[4];

    std::cout << "[INFO] Loading input image: " << inputPath << std::endl;
    cv::Mat imgSrc = cv::imread(inputPath);
    if (imgSrc.empty()) {
        std::cerr << "[ERROR] Could not load input image!" << std::endl;
        return -1;
    }
    std::cout << "[OK] Input image loaded. Size: " << imgSrc.cols << "x" << imgSrc.rows << " Channels: " << imgSrc.channels() << std::endl;

    std::cout << "[INFO] Loading seed image: " << seedPath << std::endl;
    cv::Mat imgSeed = cv::imread(seedPath);
    if (imgSeed.empty()) {
        std::cerr << "[ERROR] Could not load seed image!" << std::endl;
        return -1;
    }
    std::cout << "[OK] Seed image loaded. Size: " << imgSeed.cols << "x" << imgSeed.rows << " Channels: " << imgSeed.channels() << std::endl;

    if (imgSeed.size() != imgSrc.size()) {
        std::cerr << "[ERROR] Seed and input images must be the same size!" << std::endl;
        return -1;
    }

    if (imgSeed.channels() != 3) {
        std::cerr << "[ERROR] Seed image must be a color image (3 channels)!" << std::endl;
        return -1;
    }

    std::cout << "[INFO] Extracting foreground/background points..." << std::endl;
    std::vector<cv::Point> fore, back;
    mask2Vec(imgSeed, fore, back);
    std::cout << "[OK] Foreground points: " << fore.size() << ", Background points: " << back.size() << std::endl;

    cv::Mat result, mask;
    GraphCut::PerfMetric perf;

    std::cout << "[INFO] Running GraphCut algorithm..." << std::endl;






    GraphCut::cutImage(imgSrc, result, mask, fore, back, 0.5, -1.0, &perf);




    //    never return 


    
    std::cout << "[OK] GraphCut completed." << std::endl;

    std::cout << "[INFO] Saving output image to: " << outputPath << std::endl;
    if (!cv::imwrite(outputPath, result)) {
        std::cerr << "[ERROR] Could not write output image!" << std::endl;
        return -1;
    }

    std::cout << "[INFO] Saving mask image to: " << maskPath << std::endl;
    if (!cv::imwrite(maskPath, mask)) {
        std::cerr << "[ERROR] Could not write mask image!" << std::endl;
        return -1;
    }

    std::cout << "[OK] All outputs written successfully." << std::endl;

    std::cout << "\n--- Performance Metrics ---" << std::endl;
    std::cout << "Create N-Links: " << perf.m_tNLink << "s" << std::endl;
    std::cout << "Create T-Links: " << perf.m_tTLink << "s" << std::endl;
    std::cout << "Max Flow: " << perf.m_tMaxFlow << "s" << std::endl;

    return 0;
}
