#ifndef SVKERNELV2_H
#define SVKERNELV2_H

#include "svdefs.h"
#include "svabstractkernel.h"

class SvKernelV2: public SvAbstractKernel
{
public:
    SvKernelV2();
    virtual ~SvKernelV2();
    void exec(SvImage *image, int line) override;
    int rgbDiff(QRgb left, QRgb right);
};

#endif // SVKERNELV2_H
