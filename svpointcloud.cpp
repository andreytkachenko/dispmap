#include "svpointcloud.h"

SvPointCloud::SvPointCloud(uint width, uint height)
{
    m_pointFiledHeight = height;
    m_pointFiledWidth = width;

    m_pointField = new SvPoint* [height];

    for (uint y = 0; y < height; y++) {
        m_pointField[y] = new SvPoint[width];
    }
}

SvPointCloud::~SvPointCloud()
{
    for (uint y = 0; y < m_pointFiledHeight; y++) {
        delete[] m_pointField[y];
    }

    delete[] m_pointField;
}

void SvPointCloud::addPoint(SvFrameId frame, SvPoint point)
{
    m_pointField[point.y()][point.x()] = point;
}
