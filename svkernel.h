#ifndef SVKERNELV2_H
#define SVKERNELV2_H

#include "svdefs.h"
#include "svimage.h"
#include "svpointcloud.h"

class SvKernel
{
public:
    SvKernel();
    virtual ~SvKernel();
    void exec(SvPointCloud *pcl, SvImage *image, int line);
    int rgbDiff(QRgb left, QRgb right);
};

#endif // SVKERNELV2_H
