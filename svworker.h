#ifndef SVWORKER_H
#define SVWORKER_H

#include <QObject>
#include <QList>

#include "svkernel.h"
#include "svprocessor.h"
#include "svimage.h"

class SvProcessor;

class SvWorker : public QObject
{
    Q_OBJECT

protected:
    int          m_id;
    SvKernel    *m_kernel;
    SvProcessor *m_processor;

public:
    explicit SvWorker(QObject *parent = 0);

    void setId(int id) {m_id = id;}
    void setKernel(SvKernel* kernel) {m_kernel = kernel;}
    void setProcessor(SvProcessor* processor) {m_processor = processor;}
signals:
    void finished(int id);

public slots:
    void stop();
    void start();
};

#endif // SVWORKER_H
