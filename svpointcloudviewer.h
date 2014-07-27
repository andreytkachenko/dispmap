#ifndef SVPOINTCLOUDVIEWER_H
#define SVPOINTCLOUDVIEWER_H

#include <QQuickPaintedItem>
#include <QQuickWindow>
#include <QPainter>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>

#include "svpointcloud.h"

class SvPointCloudViewer : public QQuickPaintedItem
{
    Q_OBJECT

    //Q_PROPERTY(QObject *pointCloud READ pointCloud WRITE setPointCloud NOTIFY pointCloudChanged)

//    Q_PROPERTY(qreal cameraX READ cameraX WRITE setCameraX NOTIFY cameraXChanged)
//    Q_PROPERTY(qreal cameraY READ cameraY WRITE setCameraY NOTIFY cameraYChanged)
//    Q_PROPERTY(qreal cameraZ READ cameraZ WRITE setCameraZ NOTIFY cameraZChanged)

protected:
    SvPointCloud *m_pointCloud;
    qreal m_cameraX;
    qreal m_cameraY;
    qreal m_cameraZ;

    QOpenGLShaderProgram *m_program;

public:
    explicit SvPointCloudViewer(QQuickItem *parent = 0);
    void paint(QPainter *painter);
    void setPointCloud(SvPointCloud *pointCloud) { m_pointCloud = pointCloud; }
    SvPointCloud *pointCloud() { return m_pointCloud; }

signals:
    void pointCloudChanged();
    void cameraXChanged();
    void cameraYChanged();
    void cameraZChanged();

public slots:
    //void resetCamera();
    //void moveCamera(qreal X, qreal Y, qreal Z);
   // void rotateCamera(qreal X, qreal Y, qreal Z);
};

#endif // SVPOINTCLOUDVIEWER_H
