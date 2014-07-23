#ifndef SVPOINTCLOUD_H
#define SVPOINTCLOUD_H

#include "svdefs.h"
#include "svpoint.h"

class SvPointCloud
{
public:
    SvPointCloud();

    void addPoint(SvFrameId frame, SvPoint point);
};

#endif // SVPOINTCLOUD_H
