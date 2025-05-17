// GraphCut.h
#ifndef GRAPH_CUT_H
#define GRAPH_CUT_H

#include <opencv2/opencv.hpp>
#include <vector>

class GraphCut
{
public:
    // Performance metric (timing info)
    struct PerfMetric
    {
        double m_tNLink = 0.0;
        double m_tTLink = 0.0;
        double m_tMaxFlow = 0.0;

        PerfMetric& operator=(const PerfMetric& rhs)
        {
            m_tNLink = rhs.m_tNLink;
            m_tTLink = rhs.m_tTLink;
            m_tMaxFlow = rhs.m_tMaxFlow;
            return *this;
        }
    };

    // Main GraphCut interface
    static void cutImage(
        cv::InputArray image,
        cv::OutputArray result,
        cv::OutputArray mask,
        const std::vector<cv::Point>& foreSeeds,
        const std::vector<cv::Point>& backSeeds,
        float lambda = 0.01f,
        float sigma = -1.0f,
        PerfMetric* perfMetric = nullptr
    );
};

#endif // GRAPH_CUT_H
