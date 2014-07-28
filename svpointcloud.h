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
    uint             m_pointFieldHeight;
    uint             m_pointFieldWidth;
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

    void addPoint(SvPoint &point);
    uint getWidth() { return m_pointFieldWidth; }
    uint getHeight() { return m_pointFieldHeight; }
    SvPoint *point(uint x, uint y) { return m_pointField[y][x]; }
};

#endif // SVPOINTCLOUD_H
