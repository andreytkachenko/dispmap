#ifndef SVABSTRACTKERNEL_H
#define SVABSTRACTKERNEL_H

#include "svimage.h"
#include "svpointcloud.h"

class SvAbstractKernel
{

protected:
    SvImage* m_image;
    SvPointCloud* m_pointCloud;

public:
    void setImage(SvImage* image) {m_image = image;}
    void setPointCloud(SvPointCloud* pointCloud) {m_pointCloud = pointCloud;}
    virtual void exec(int line) = 0;
    virtual ~SvAbstractKernel() {}
};

#endif // SVABSTRACTKERNEL_H
