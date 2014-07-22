#ifndef SVKERNELV2_H
#define SVKERNELV2_H

#include "svabstractkernel.h"
#include <QDebug>
#define sign(a) (a == 0 ? 0 : (a > 0 ? 1 : -1))
#define max(a,b,c) (a > b ? (a > c ? a : c) : (b > c ? b : c))
#define min(a,b,c) (a < b ? (a < c ? a : c) : (b < c ? b : c))

class SvKernelV2: public SvAbstractKernel
{
public:
    SvKernelV2();
    virtual ~SvKernelV2();
    void exec(int line) override;
    int rgbDiff(QRgb left, QRgb right);
};

#endif // SVKERNELV2_H
