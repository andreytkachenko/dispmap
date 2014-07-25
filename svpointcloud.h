#ifndef SVPOINTCLOUD_H
#define SVPOINTCLOUD_H

#include "svdefs.h"
#include "svpoint.h"
#include "svcurve.h"
#include "svfigure.h"
#include "svobject.h"

class SvCurve;
class SvFigure;
class SvObject;

class SvPointCloud
{
protected:
    uint             m_pointFiledHeight;
    uint             m_pointFiledWidth;
    SvPoint**        m_pointField;
    QList<SvCurve*>  m_curves;
    QList<SvFigure*> m_figures;
    QList<SvObject*> m_objects;

public:
    SvPointCloud(uint width, uint height);
    ~SvPointCloud();

    void addPoint(SvFrameId frame, SvPoint point);

};

#endif // SVPOINTCLOUD_H
