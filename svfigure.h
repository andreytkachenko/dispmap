#ifndef SVFIGURE_H
#define SVFIGURE_H

#include "svpoint.h"
#include "svcurve.h"

class SvFigure
{
protected:
    QColor          m_color;
    QList<SvCurve*> m_curves;

public:
    SvFigure(SvCurve *curve);

    void addCurve(SvCurve *curve){m_curves.pop_back(curve); }
    SvCurve *findCurveByPoint();
    SvFigure split(SvPoint *point);
};

#endif // SVFIGURE_H
