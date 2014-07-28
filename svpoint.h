#ifndef SVPOINT_H
#define SVPOINT_H

#include "svsimplepoint.h"
#include "svdefs.h"

class SvCurve;

class SvPoint: public SvSimplePoint
{

public:
    enum Sides {
        TOP,
        BOTTOM,
        RIGHT,
        LEFT
    };

    enum FlowType {
        HORIZONTAL,
        VERTICAL,
        SLASH,
        BACK_SLASH
    };

protected:
    uint      m_id;
    uint      m_curveCount;
    SvCurve  *m_curves[8];
    FlowType  m_type;
    QRgb      m_color;

public:
    SvPoint();
    SvPoint(SvPoint &point);

    void addCurve(SvCurve *curve);
    uint curveCount() {return m_curveCount; }
    QRgb color() { return m_color; }
    void setColor(QRgb color) { m_color = color; }
    SvCurve *curve(uint index) {return m_curves[index]; }
};

#endif // SVPOINT_H
