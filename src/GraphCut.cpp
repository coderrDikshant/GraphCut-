// GraphCut.cpp
#include <iostream>
#include "StopWatch.h"
#include "GraphCutImpl.h"
#include "GraphCut.h"

void GraphCut::cutImage(
    cv::InputArray image,
    cv::OutputArray result,
    cv::OutputArray mask,
    const std::vector<cv::Point>& foreSeeds,
    const std::vector<cv::Point>& backSeeds,
    float lambda,
    float sigma,
    PerfMetric* perfMetric
) {
    GraphCutImpl GC(image, foreSeeds, backSeeds);

    // Set parameters if explicitly provided
    if (lambda >= 0.0f) GC.m_Lambda = lambda;
    if (sigma >= 0.0f)  GC.m_Sigma = sigma;

    // Run the actual graph cut
    GC.cutImage(image, result, mask);

    // Pass back performance metrics if needed
    if (perfMetric) {
        *perfMetric = GC.m_perfMetric;
    }
}
