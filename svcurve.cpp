#include "svcurve.h"

SvCurve::SvCurve()
{
}

void SvCurve::addPoint(SvPoint *point)
{
    m_points.push_back(point);
}

bool SvCurve::hasPoint(SvPoint *point)
{
    foreach (SvPoint *item, m_points) {
        if (point == item) {
            return true;
        }
    }

    return false;
}

SvCurve *SvCurve::cut(SvPoint *point)
{

}
