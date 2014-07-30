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
    QList<SvSimplePoint*> m_keyPoints;

private:
    SvCurve();

public:
    QList<SvPoint*> &points() {return m_points; }
    SvPoint* head() {return m_points.first(); }
    SvPoint* tail() {return m_points.last(); }
    void setInner(SvFigure *figure) {m_inner = figure; }
    void setOuter(SvFigure *figure) {m_outer = figure; }
    void addPoint(SvPoint *point);
    bool hasPoint(SvPoint *point);
    SvCurve *cut(SvPoint *point);
};

#endif // SVCURVE_H
