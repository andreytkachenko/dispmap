#include "svcurve.h"

SvCurve::SvCurve()
{
}

void SvCurve::addPoint(SvPoint *point)
{
    m_points.push_back(point);
}

SvCurve *SvCurve::cut(SvPoint *point)
{

}
