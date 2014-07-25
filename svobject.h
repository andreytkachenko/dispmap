#ifndef SVOBJECT_H
#define SVOBJECT_H

#include "svfigure.h"

class SvFigure;


class SvObject
{
protected:
    SvFigure *m_figures;

public:
    SvObject();
};

#endif // SVOBJECT_H
