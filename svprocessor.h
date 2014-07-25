#ifndef SVPROCESSOR_H
#define SVPROCESSOR_H

#include <time.h>

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QQueue>
#include <QMutex>
#include <QException>

#include "svimage.h"
#include "svworker.h"
#include "svkernel.h"
#include "svpointcloud.h"


class SvWorker;

class SvNoMoreTasks: public QException
{

};

class SvProcessor: public QObject
{
    Q_OBJECT

protected:
    QThread*    m_threads;
    SvWorker*   m_workers;
    SvKernel*   m_kernel;
    uint        m_numberOfWorkers;
    uint        m_workersFinished;
    uint        m_startTime;
    QQueue<SvProcessorTask*> m_taskQueue;
    QMutex      m_nextTaskMutex;

public:
    explicit SvProcessor(QObject *parent = 0);
    SvProcessor(int numberOfWorkers = 1);
    ~SvProcessor();
    void execute();
    void enqueueImage(SvPointCloud *pointCloud, SvImage *image);
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
