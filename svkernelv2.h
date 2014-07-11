#ifndef SVKERNELV2_H
#define SVKERNELV2_H

#include "svabstractkernel.h"

class SvKernelV2: public SvAbstractKernel
{
public:
    SvKernelV2();
    virtual ~SvKernelV2();
    void exec(int line) override;
};

#endif // SVKERNELV2_H
