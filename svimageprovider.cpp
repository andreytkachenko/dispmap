#include "svimageprovider.h"

SvImageProvider::SvImageProvider():
    QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage SvImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(requestedSize)

    SvImage* image = m_images[id];

    if (image) {
        *size = QSize(image->getWidth(), image->getHeight());

        return image->getImage();
    }

    return QImage(0, 0, QImage::Format_RGB32);
}

void SvImageProvider::addImage(const QString &name, SvImage *image)
{
    m_images[name] = image;
}
