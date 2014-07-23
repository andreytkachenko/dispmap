#ifndef SVPROCESSOR_H
#define SVPROCESSOR_H

#include <time.h>

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QQueue>
#include <QMutex>

#include "svimage.h"
#include "svworker.h"
#include "svabstractkernel.h"
#include "svkernelv1.h"
#include "svkernelv2.h"
#include "svpointcloud.h"


typedef struct {
    SvImage *image;
    int      line;
} SvProcessorTask;


class SvProcessor: public QObject
{
    Q_OBJECT

protected:
    QThread*            m_threads;
    SvWorker*           m_workers;
    SvAbstractKernel*   m_kernel;
    unsigned int        m_numberOfWorkers;
    unsigned int        m_workersFinished;
    unsigned int        m_startTime;
    QQueue<SvProcessorTask*> m_queue;
    QMutex              m_nextTaskMutex;

public:
    explicit SvProcessor(QObject *parent = 0);
    SvProcessor(SvPointCloud *pointCloud, int numberOfWorkers = 1, int version = 1);
    ~SvProcessor();
    void execute();
    void enqueueImage(SvFrameId frame, SvImage *image);

protected:
    SvProcessorTask nextTask();

protected slots:
    void workerFinished(int workerId);

public slots:
    void start();
    void stop();

signals:
    void started();
    void finished(int elapsedTime);
    void stopped(int elapsedTime);
};

#endif // SVPROCESSOR_H
