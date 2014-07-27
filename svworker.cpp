#include "svworker.h"

SvWorker::SvWorker(QObject *parent) :
    QObject(parent)
{

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

        m_kernel->exec(task.pointCloud, task.image, task.line);
    }

    emit finished(m_id);
}
