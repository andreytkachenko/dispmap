#ifndef SVFIGURE_H
#define SVFIGURE_H

#include <QColor>

#include "svpoint.h"
#include "svcurve.h"

class SvFigure
{
protected:
    QColor          m_color;
    QList<SvCurve*> m_curves;

public:
    SvFigure();
    SvFigure(SvCurve *curve);

    void addCurve(SvCurve *curve){m_curves.push_back(curve); }
    SvCurve *findCurveByPoint(SvPoint *point);
    SvFigure split(SvPoint *point);
};

#endif // SVFIGURE_H
