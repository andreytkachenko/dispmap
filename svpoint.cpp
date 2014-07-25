#include "svpoint.h"

SvPoint::SvPoint()
{

}

SvPoint::SvPoint(SvPoint &point)
{

}

void SvPoint::addCurve(SvCurve *curve)
{
    m_curves[m_curveCount++] = curve;
}
