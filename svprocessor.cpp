#include "svprocessor.h"

SvProcessor::SvProcessor(QObject *parent):
    QObject(parent)
{

}

SvProcessor::SvProcessor(int numberOfWorkers)
{
    uint i;

    m_kernel = new SvKernel();

    m_numberOfWorkers = numberOfWorkers;
    m_workers = new SvWorker[m_numberOfWorkers];
    m_threads = new QThread[m_numberOfWorkers];

    for (i = 0; i < m_numberOfWorkers; i++) {
        m_workers[i].setId(i);
        m_workers[i].setKernel(m_kernel);
        m_workers[i].setProcessor(this);
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

void SvProcessor::enqueueImage(SvPointCloud *pointCloud, SvImage *image)
{
    SvProcessorTask *task;

    for (uint i = 0; i < image->getHeight(); i++) {
        task = new SvProcessorTask;
        task->image = image;
        task->line  = i;
        task->pointCloud = pointCloud;
        m_taskQueue.enqueue(task);
    }
}

SvProcessorTask SvProcessor::nextTask()
{
    SvProcessorTask  task, *taskPtr;

    m_nextTaskMutex.lock();

    if (!m_taskQueue.size()) {
        m_nextTaskMutex.unlock();
        throw SvNoMoreTasks();
    }

    taskPtr = m_taskQueue.dequeue();

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
    uint i;

    m_startTime = time(NULL);
    m_workersFinished = 0;

    for (i = 0; i < m_numberOfWorkers; i++) {
        m_threads[i].start(QThread::HighPriority);
    }
}

void SvProcessor::stop()
{
    emit stopped(time(NULL) - m_startTime);
}
