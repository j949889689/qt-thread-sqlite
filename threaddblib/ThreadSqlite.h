#ifndef THREADSQLITE_H
#define THREADSQLITE_H

#include "ThreadSqliteObject.h"

#include <QObject>

class QThread;
class QEventLoop;
class ThreadSqlite : public QObject
{
    Q_OBJECT
public:
    ThreadSqlite(QObject * parent = nullptr);
    ~ThreadSqlite();
    bool open(QString const & path,QString const & connectionName);
    void close();
    void closeExec();
    void exec(QString const & sql);
    void exec(QString const & sql,QSharedPointer<QVariantMap> values);
    void exec(QString const & sql,QSharedPointer<QVariantMap> values,QSharedPointer<ThreadSqlQueryInterface> query);
public:
signals:
    void execSignals(QString const &,QSharedPointer<QVariantMap>,QSharedPointer<ThreadSqlQueryInterface>);
    void initSqlite();
    void closeSqlite();
private slots:
    void execDone(QSharedPointer<ThreadSqlQueryInterface> query);
    void closeDone();
private:
    QThread * thread;
    QEventLoop * eventLoop;
    ThreadSqliteObject threadSqliteObject;
};

#endif // THREADSQLITE_H
