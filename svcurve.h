#ifndef SVCURVE_H
#define SVCURVE_H

#include <QColor>

#include "svdefs.h"
#include "svpoint.h"
#include "svsimplepoint.h"

class SvPoint;

class SvCurve
{
protected:
    SvPoint *m_ends;
    SvPoint *m_points;
    SvSimplePoint *m_keyPoints;
    QColor m_leftColor;
    QColor m_rightColor;


public:
    SvCurve();
};

#endif // SVCURVE_H
