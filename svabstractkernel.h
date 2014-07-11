#ifndef SVABSTRACTKERNEL_H
#define SVABSTRACTKERNEL_H

#include "svimage.h"

class SvAbstractKernel
{

protected:
    SvImage* m_left;
    SvImage* m_right;
    SvImage* m_result;

public:
    void setLeftImage(SvImage* image) {m_left = image;}
    void setRightImage(SvImage* image) {m_right = image;}
    void setResultImage(SvImage* image) {m_result = image;}
    virtual void exec(int line) = 0;
    virtual ~SvAbstractKernel() {}
};

#endif // SVABSTRACTKERNEL_H
