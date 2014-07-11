#ifndef SVWORKER_H
#define SVWORKER_H

#include <QObject>
#include <QList>

#include "svabstractkernel.h"
#include "svimage.h"

class SvWorker : public QObject
{
    Q_OBJECT

protected:
    int                 m_id;
    SvAbstractKernel*   m_kernel;
    QList<unsigned int> m_tasks;

public:
    explicit SvWorker(QObject *parent = 0);
    SvWorker(SvAbstractKernel* kernel);

    void setId(int id) {m_id = id;}
    void addTask(int line) {m_tasks << line;}
    void setKernel(SvAbstractKernel* kernel) {m_kernel = kernel;}

signals:
    void finished(int id);

public slots:
    void stop();
    void start();

};

#endif // SVWORKER_H
