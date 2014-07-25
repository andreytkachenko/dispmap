#include "svpointcloudviewer.h"

SvPointCloudViewer::SvPointCloudViewer(QQuickItem *parent) :
    QQuickItem(parent)
{

}

void SvPointCloudViewer::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing,
                this, &SvPointCloudViewer::sync, Qt::DirectConnection);

        connect(win, &QQuickWindow::sceneGraphInvalidated,
                this, &SvPointCloudViewer::cleanup, Qt::DirectConnection);
    }
}

void SvPointCloudViewer::sync()
{
    if (!m_pointCloudRenderer) {
        m_pointCloudRenderer = new SvPointCloudRenderer();
        connect(window(), &QQuickWindow::beforeRendering,
                m_pointCloudRenderer, &SvPointCloudRenderer::paint, Qt::DirectConnection);
    }

    m_pointCloudRenderer->setViewportSize(window()->size() * window()->devicePixelRatio());
}

void SvPointCloudViewer::cleanup()
{
    if (m_pointCloudRenderer) {
        delete m_pointCloudRenderer;
        m_pointCloudRenderer = 0;
    }
}
