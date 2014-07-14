#ifndef SVIMAGEPROVIDER_H
#define SVIMAGEPROVIDER_H

#include <QtQuick/QQuickImageProvider>
#include <QHash>

#include "svimage.h"

#include <QDebug>

class SvImageProvider : public QQuickImageProvider
{
protected:
    QHash<QString, SvImage*> m_images;

public:
    SvImageProvider();
    virtual QImage requestImage(const QString &id, QSize *size, const QSize& requestedSize);
    void addImage(const QString &name, SvImage* image);
};

#endif // SVIMAGEPROVIDER_H
