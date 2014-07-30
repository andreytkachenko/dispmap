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
    int x = point.x(),
        y = point.y();

    SvPoint *topLeft,    *top,    *topRight;
    SvPoint *left,       *center, *right;
    SvPoint *bottomLeft, *bottom, *bottomRight;

    center = m_pointField[y][x - 1];

    if (y > 1 && y < m_pointFieldHeight - 1 &&
        x > 1 && x < m_pointFieldWidth && center) {

        topRight    = m_pointField[y - 1][x    ];
        top         = m_pointField[y - 1][x - 1];
        topLeft     = m_pointField[y - 1][x - 2];
        right       = new SvPoint(point);
        left        = m_pointField[y    ][x - 2];
        bottomRight = m_pointField[y + 1][x    ];
        bottom      = m_pointField[y + 1][x - 1];
        bottomLeft  = m_pointField[y + 1][x - 2];





    }

    m_pointField[y][x] = right;
}
