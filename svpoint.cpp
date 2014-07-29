#include "svpoint.h"

SvPoint::SvPoint()
{

}

SvPoint::SvPoint(SvPoint &point)
{
    m_px    = point.x();
    m_py    = point.y();
    m_color = point.color();
}

void SvPoint::addCurve(SvCurve *curve)
{
    m_curves[m_curveCount++] = curve;
}
