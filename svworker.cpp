#include "svworker.h"

SvWorker::SvWorker(QObject *parent) :
    QObject(parent)
{

}

SvWorker::SvWorker(SvProcessorTask *processor, SvAbstractKernel *kernel)
{
    m_processor = processor;
    m_kernel = kernel;
}

void SvWorker::stop()
{

}

void SvWorker::start()
{
    SvProcessorTask task;

    while(true) {
        try {
            task = m_processor->nextTask();
        } catch (SvNoMoreTasks ex) {
            break;
        }

        m_kernel->exec(task.image, task.line);
    }

    emit finished(m_id);
}
