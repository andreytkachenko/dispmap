#ifndef SVPOINT_H
#define SVPOINT_H

#include "svsimplepoint.h"
#include "svcurve.h"

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
    SvCurve* m_curves;
    FlowType m_type;

public:
    SvPoint();
};

#endif // SVPOINT_H
