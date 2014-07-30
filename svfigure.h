#ifndef SVFIGURE_H
#define SVFIGURE_H

#include <QColor>

#include "svpoint.h"
#include "svcurve.h"

class SvFigure
{
protected:
    QRgb            m_color;
    QList<SvCurve*> m_curves;

public:
    SvFigure();
    SvFigure(SvCurve *curve);

    QRgb color() {return m_color;}
    void addCurve(SvCurve *curve){m_curves.push_back(curve); }
    QList<SvCurve*> &curves() { return m_curves; }
    SvCurve *findCurveByPoint(SvPoint *point);
    SvFigure split(SvPoint *point);
};

#endif // SVFIGURE_H
