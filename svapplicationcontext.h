#ifndef SVPOINTCLOUDVIEWMODEL_H
#define SVPOINTCLOUDVIEWMODEL_H

#include <QObject>

#include "svpointcloud.h"

class SvApplicationContext : public QObject
{
    Q_OBJECT

public:
    explicit SvApplicationContext(QObject *parent = 0);

    void setPointCloud(SvPointCloud *pointCloud) { m_pointCloud = pointCloud; }
    Q_INVOKABLE SvPointCloud* pointCloud() { return m_pointCloud; }

private:
    SvPointCloud *m_pointCloud;
};

#endif // SVPOINTCLOUDVIEWMODEL_H
