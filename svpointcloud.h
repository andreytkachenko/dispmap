#ifndef SVPOINTCLOUD_H
#define SVPOINTCLOUD_H

#include <QObject>

#include "svdefs.h"
#include "svpoint.h"
#include "svcurve.h"
#include "svfigure.h"
#include "svobject.h"

class SvCurve;
class SvFigure;
class SvObject;

class SvPointCloud: public QObject
{
    Q_OBJECT

    friend class SvCurve;
    friend class SvPoint;
    friend class SvFigure;
    friend class SvObject;

protected:
    uint             m_pointFiledHeight;
    uint             m_pointFiledWidth;
    SvPoint***       m_pointField;
    QList<SvCurve*>  m_curves;
    QList<SvFigure*> m_figures;
    QList<SvObject*> m_objects;

public:
    SvPointCloud(uint width, uint height);
    ~SvPointCloud();

    SvCurve  *createCurve();
    SvFigure *createFigure();
    SvObject *createObject();

    void addPoint(SvPoint point);
};

#endif // SVPOINTCLOUD_H
