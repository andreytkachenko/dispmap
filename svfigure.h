#ifndef SVFIGURE_H
#define SVFIGURE_H

#include "svpoint.h"
#include "svcurve.h"

class SvFigure
{
protected:
    SvPoint ends[2];


public:
    SvFigure();
};

#endif // SVFIGURE_H
