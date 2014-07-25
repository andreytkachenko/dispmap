#ifndef SVPOINTCLOUDRENDERER_H
#define SVPOINTCLOUDRENDERER_H

#include <QObject>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>

class SvPointCloudRenderer : public QObject
{
    Q_OBJECT
public:
    explicit SvPointCloudRenderer(QObject *parent = 0);
    void setViewportSize(const QSize &size) { m_viewportSize = size; }

public slots:
    void paint();

private:
    QSize m_viewportSize;
    qreal m_t;
    QOpenGLShaderProgram *m_program;
};

#endif // SVPOINTCLOUDRENDERER_H
