#include "svfigure.h"

SvFigure::SvFigure(SvCurve *curve)
{
    addCurve(curve);
}

SvFigure::SvFigure()
{
}

SvCurve *SvFigure::findCurveByPoint(SvPoint *point)
{
    foreach(SvCurve* curve, m_curves) {
        if (curve->hasPoint(point)) {
            return curve;
        }
    }

    return 0;
}

SvFigure SvFigure::split(SvPoint *point)
{
    SvCurve *curve = findCurveByPoint(point);
    SvFigure figure;

    if (curve) {
        figure.addCurve(curve->cut(point));
        SvCurve *item = m_curves.last();

        while(item != curve) {
            figure.addCurve(item);

            m_curves.removeLast();
            item = m_curves.last();
        }
    }

    return figure;
}
