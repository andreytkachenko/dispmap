#include "svprocessor.h"

SvProcessor::SvProcessor(QObject *parent):
    QObject(parent)
{

}

SvProcessor::SvProcessor(SvPointCloud* pointCloud, int numberOfWorkers, int version)
{
    unsigned int i;

    if (version == 1) {
        m_kernel = new SvKernelV1();
    } else if (version == 2) {
        m_kernel = new SvKernelV2();
    }

    m_kernel->setPointCloud(pointCloud);
    m_numberOfWorkers = numberOfWorkers;
    m_workers = new SvWorker[m_numberOfWorkers];
    m_threads = new QThread[m_numberOfWorkers];

    for (i = 0; i < m_numberOfWorkers; i++) {
        m_workers[i].setId(i);
        m_workers[i].setKernel(m_kernel);
        m_workers[i].moveToThread(&m_threads[i]);

        connect(&m_threads[i], &QThread::started, &m_workers[i], &SvWorker::start);
        connect(&m_workers[i], &SvWorker::finished, this, &SvProcessor::workerFinished);
    }
}

SvProcessor::~SvProcessor()
{
    delete   m_kernel;
    delete[] m_workers;
}

void SvProcessor::enqueueImage(SvFrameId frame, SvImage *image)
{
    SvProcessorTask *task;

    for (int i = 0; i < image->getHeight(); i++) {
        task = new SvProcessorTask;
        task->image = image;
        task->line  = i;
        m_queue.enqueue(task);
    }
}

SvProcessorTask SvProcessor::nextTask()
{
    SvProcessorTask  task;
    SvProcessorTask *taskPtr;

    m_nextTaskMutex.lock();
    taskPtr = m_queue.dequeue();
    m_nextTaskMutex.unlock();
    task = *taskPtr;
    delete taskPtr;

    return task;
}

void SvProcessor::workerFinished(int workerId)
{
    qDebug() << "worker " << workerId  << " finished";
    m_workersFinished++;
    if (m_workersFinished == m_numberOfWorkers) {
        qDebug() << "finished";
        emit finished(time(NULL) - m_startTime);
    }
}

void SvProcessor::start()
{
    unsigned int i;

    m_startTime = time(NULL);
    m_workersFinished = 0;

    for (i = 0; i < m_numberOfWorkers; i++) {
        m_threads[i].start(QThread::HighestPriority);
    }
}

void SvProcessor::stop()
{
    emit stopped(time(NULL) - m_startTime);
}
