#ifndef SVCURVE_H
#define SVCURVE_H

#include "svpoint.h"

class SvPoint;

class SvCurve
{
protected:
    SvPoint *m_ends;
    SvPoint *m_points;
    SvSimplePoint *m_keyPoints;

public:
    SvCurve();
};

#endif // SVCURVE_H
