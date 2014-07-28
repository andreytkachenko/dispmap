#include "svpointcloud.h"
#include <string.h>

SvPointCloud::SvPointCloud(uint width, uint height)
{
    m_pointFieldHeight = height;
    m_pointFieldWidth = width;

    m_pointField = new SvPoint**[height];

    for (uint y = 0; y < height; y++) {
        m_pointField[y] = new SvPoint*[width];
        memset(m_pointField[y], 0, sizeof(SvPoint*) * width);
    }
}

SvPointCloud::~SvPointCloud()
{
    for (uint y = 0; y < m_pointFieldHeight; y++) {
        for (uint x = 0; x < m_pointFieldWidth; x++) {
            if (m_pointField[y][x]) {
                delete m_pointField[y][x];
            }
        }

        delete[] m_pointField[y];
    }

    delete[] m_pointField;
}

void SvPointCloud::addPoint(SvPoint &point)
{
    m_pointField[point.y()][point.x()] = new SvPoint(point);
}
