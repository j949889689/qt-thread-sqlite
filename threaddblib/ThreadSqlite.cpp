#include "ThreadSqlite.h"
#include <QThread>
#include <QDebug>
#include <QEventLoop>

ThreadSqlite::ThreadSqlite(QObject * parent)
    : QObject{parent}
    , thread(nullptr)
    , eventLoop(nullptr)
{
    thread = new QThread(this);
    connect(this,&ThreadSqlite::execSignals,&threadSqliteObject,&ThreadSqliteObject::exec,Qt::QueuedConnection);
    connect(&threadSqliteObject,&ThreadSqliteObject::execDone,this,&ThreadSqlite::execDone,Qt::QueuedConnection);
    connect(this,&ThreadSqlite::initSqlite,&threadSqliteObject,&ThreadSqliteObject::initSqlite,Qt::QueuedConnection);
    connect(this,&ThreadSqlite::closeSqlite,&threadSqliteObject,&ThreadSqliteObject::closeSqlite,Qt::QueuedConnection);
    connect(&threadSqliteObject,&ThreadSqliteObject::closeDone,this,&ThreadSqlite::closeDone,Qt::QueuedConnection);
}

ThreadSqlite::~ThreadSqlite()
{
    if(thread->isRunning()){
        close();
    }
    thread->deleteLater();
}

bool ThreadSqlite::open(const QString &path,QString const & connectionName)
{
    if(thread->isRunning()){
        qWarning()<<"Database has been opened";
        return false;
    }
    threadSqliteObject.setPath(path);
    threadSqliteObject.setConnectionName(connectionName);
    threadSqliteObject.moveToThread(thread);
    thread->start();
    emit initSqlite();
    return true;
}

void ThreadSqlite::close()
{
    emit closeSqlite();
}

void ThreadSqlite::closeExec()
{
    emit closeSqlite();
    eventLoop = new QEventLoop();
    eventLoop->exec();
}

void ThreadSqlite::exec(const QString &sql)
{
    if(!thread->isRunning()){
        qWarning()<<"The database is close";
        return;
    }
    emit execSignals(sql,QSharedPointer<QVariantMap>(),QSharedPointer<ThreadSqlQueryInterface>());
}

void ThreadSqlite::exec(const QString &sql, QSharedPointer<QVariantMap> values)
{
    if(!thread->isRunning()){
        qWarning()<<"The database is close";
        return;
    }
    emit execSignals(sql,values,QSharedPointer<ThreadSqlQueryInterface>());
}

void ThreadSqlite::exec(const QString &sql, QSharedPointer<QVariantMap> values, QSharedPointer<ThreadSqlQueryInterface> query)
{
    emit execSignals(sql,values,query);
}

void ThreadSqlite::execDone(QSharedPointer<ThreadSqlQueryInterface> query)
{
    if(!query.isNull()){
        query->dealQuery();
    }
}

void ThreadSqlite::closeDone()
{
    thread->quit();
    thread->wait();
    if(eventLoop != nullptr){
        eventLoop->quit();
        eventLoop->deleteLater();
        eventLoop = nullptr;
    }
}
