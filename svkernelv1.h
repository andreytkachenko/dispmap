#ifndef SVKERNELV1_H
#define SVKERNELV1_H

#include "svabstractkernel.h"

class SvKernelV1: public SvAbstractKernel
{

protected:
    int m_windowSize = 80;

public:
    void exec(int line) override;
    SvKernelV1();
    virtual ~SvKernelV1();

protected:
    int getPixelColor(int cursor);
    int diff(int lx, int ly, int rx, int ry);
    int match(int x, int y, int i);
};

#endif // SVKERNELV1_H
