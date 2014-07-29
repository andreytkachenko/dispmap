#include "svpointcloudviewer.h"

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>

SvPointCloudViewer::SvPointCloudViewer(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    setRenderTarget(QQuickPaintedItem::FramebufferObject);
}

void SvPointCloudViewer::paint(QPainter *painter)
{
    if (!m_pointCloud) {
        qDebug() << "point cloud not set!";
        return;
    }

    painter->beginNativePainting();

    glViewport(0, 0, width(), height());

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    //glEnable (GL_BLEND);
    //glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();
    glTranslatef(100.0f, height()-10, -40.0f);

    glBegin(GL_POINTS);
        for (int y = 0; y < m_pointCloud->getHeight(); y++) {
            for (int x = 0; x < m_pointCloud->getWidth(); x++) {
                SvPoint *p = m_pointCloud->point(x, y);
                if (p) {
                    glColor3ub(qRed(p->color()), qGreen(p->color()), qBlue(p->color()));
                    glVertex3i(x, -y, 0);
                }
            }
        }
    glEnd();

    painter->endNativePainting();
}

