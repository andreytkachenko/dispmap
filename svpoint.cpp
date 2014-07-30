#include "svpoint.h"

SvPoint::SvPoint()
{

}

SvPoint::SvPoint(SvPoint &point)
{
    (*this) = point;
}

void SvPoint::addCurve(SvCurve *curve)
{
    m_curves[m_curveCount++] = curve;
}

int SvPoint::parallelism(SvPoint *p, DiffType type)
{

}


void SvPoint::setDiff(int lDiff, int ltDiff, int tDiff, int rtDiff)
{
    m_diff[LEFT] = lDiff;
    m_diff[LEFT_TOP] = ltDiff;
    m_diff[TOP] = tDiff;
    m_diff[RIGHT_TOP] = rtDiff;
}
