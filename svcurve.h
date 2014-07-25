#ifndef SVCURVE_H
#define SVCURVE_H

#include "svdefs.h"
#include "svpoint.h"
#include "svsimplepoint.h"

class SvPoint;
class SvFigure;

class SvCurve
{
protected:
    SvFigure *m_inner;
    SvFigure *m_outer;

    QList<SvPoint*> m_points;
    SvSimplePoint *m_keyPoints;

private:
    SvCurve();

public:
    SvPoint* head() {return m_points.first(); }
    SvPoint* tail() {return m_points.last(); }
    SvPoint* tail() {return m_points.last(); }
    void setInner(SvFigure *figure) {m_inner = figure; }
    void setOuter(SvFigure *figure) {m_outer = figure; }
    void addPoint(SvPoint *point);
    SvCurve *cut(SvPoint *point);
};

#endif // SVCURVE_H
