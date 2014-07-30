#ifndef SVPOINT_H
#define SVPOINT_H

#include "svsimplepoint.h"
#include "svdefs.h"

class SvCurve;

class SvPoint: public SvSimplePoint
{

public:
    enum DiffType {
        LEFT      = 0,
        LEFT_TOP  = 1,
        TOP       = 2,
        RIGHT_TOP = 3
    };

protected:
    uint      m_id;
    uint      m_curveCount;
    SvCurve  *m_curves[8];
    int       m_diff[4];
    QRgb      m_colors[4];

public:
    SvPoint();
    SvPoint(SvPoint &point);

    void addCurve(SvCurve *curve);
    uint curveCount() {return m_curveCount; }
    SvCurve *curve(uint index) { return m_curves[index]; }

    int  parallelism(SvPoint *p, DiffType type);
    int  diff(DiffType index) { return m_diff[index]; }
    void setDiff(int lDiff, int ltDiff, int tDiff, int rtDiff);
    void setColors(QRgb left, QRgb top, QRgb right, QRgb bottom);
};

#endif // SVPOINT_H
