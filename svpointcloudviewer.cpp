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
    glLoadIdentity();
    glTranslatef(0.0f, height(), -40.0f);
    glPointSize(1.0f);
    glScalef(1.0f, 1.0f, 1.0f);

    foreach (SvFigure *figure, m_pointCloud->figures()) {
        glBegin(GL_POLYGON);
        glColor3ub(qRed(figure->color()), qGreen(figure->color()), qBlue(figure->color()));

        foreach (SvCurve *curve, figure->curves()) {
            foreach (SvPoint *point, curve->points()) {
                glVertex3i(point->x(), point->y(), 0);
            }
        }

        glEnd();
    }

    painter->endNativePainting();
}


/*
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
    glLoadIdentity();
    glTranslatef(0.0f, height(), -40.0f);
    glPointSize(1.0f);
    glScalef(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);
        for (int y = 1; y < m_pointCloud->getHeight(); y++) {
            for (int x = 1; x < m_pointCloud->getWidth() - 1; x++) {
                SvPoint *lp = m_pointCloud->point(x - 1, y);
                SvPoint *tlp = m_pointCloud->point(x - 1, y - 1);
                SvPoint *tp = m_pointCloud->point(x, y - 1);
                SvPoint *trp = m_pointCloud->point(x + 1, y - 1);
                SvPoint *p = m_pointCloud->point(x, y);
                if (p) {
                    //glColor3ub(0, 0, 0);

                    int topRight = abs(p->diff(SvPoint::RIGHT_TOP));
                    int topLeft = abs(p->diff(SvPoint::LEFT_TOP));
                    int left = abs(p->diff(SvPoint::LEFT));
                    int top = abs(p->diff(SvPoint::TOP));

                    glColor3ub(top * 4 > 255 ? 255 : top * 4, left * 4 > 255 ? 255 : left * 4, 0);
                }
            }
        }
    glEnd();

    painter->endNativePainting();
}
*/
