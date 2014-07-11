#include "svworker.h"

SvWorker::SvWorker(QObject *parent) :
    QObject(parent)
{

}

SvWorker::SvWorker(SvAbstractKernel* kernel)
{
    m_kernel = kernel;
}

void SvWorker::stop()
{

}

void SvWorker::start()
{
    for (int i: m_tasks) {
        m_kernel->exec(i);
    }

    emit finished(m_id);
}
