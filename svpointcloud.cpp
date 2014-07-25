#include "svpointcloud.h"

SvPointCloud::SvPointCloud(uint width, uint height)
{
    m_pointFiledHeight = height;
    m_pointFiledWidth = width;

    m_pointField = new SvPoint**[height]();

    for (uint y = 0; y < height; y++) {
        m_pointField[y] = new SvPoint*[width]();
    }
}

SvPointCloud::~SvPointCloud()
{
    for (uint y = 0; y < m_pointFiledHeight; y++) {
        for (uint x = 0; x < m_pointFiledWidth; x++) {
            if (m_pointField[y][x]) {
                delete m_pointField[y][x];
            }
        }

        delete[] m_pointField[y];
    }

    delete[] m_pointField;
}

void SvPointCloud::addPoint(SvPoint point)
{
    m_pointField[point.y()][point.x()] = new SvPoint(point);
}
