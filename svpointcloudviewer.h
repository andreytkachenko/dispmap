#ifndef SVPOINTCLOUDVIEWER_H
#define SVPOINTCLOUDVIEWER_H

#include <QQuickItem>
#include <QQuickWindow>

#include "svpointcloud.h"
#include "svpointcloudrenderer.h"

class SvPointCloudViewer : public QQuickItem
{
    Q_OBJECT

//    Q_PROPERTY(qreal cameraX READ cameraX WRITE setCameraX NOTIFY cameraXChanged)
//    Q_PROPERTY(qreal cameraY READ cameraY WRITE setCameraY NOTIFY cameraYChanged)
//    Q_PROPERTY(qreal cameraZ READ cameraZ WRITE setCameraZ NOTIFY cameraZChanged)

protected:
    SvPointCloud *pointCloud;
    SvPointCloudRenderer *m_pointCloudRenderer;
    qreal m_cameraX;
    qreal m_cameraY;
    qreal m_cameraZ;

public:
    explicit SvPointCloudViewer(QQuickItem *parent = 0);

signals:
    void cameraXChanged();
    void cameraYChanged();
    void cameraZChanged();

private slots:
    void handleWindowChanged(QQuickWindow *win);

public slots:
    void sync();
    void cleanup();
    //void resetCamera();
    //void moveCamera(qreal X, qreal Y, qreal Z);
   // void rotateCamera(qreal X, qreal Y, qreal Z);
};

#endif // SVPOINTCLOUDVIEWER_H
