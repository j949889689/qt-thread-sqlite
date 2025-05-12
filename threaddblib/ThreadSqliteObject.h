#ifndef THREADSQLITEOBJECT_H
#define THREADSQLITEOBJECT_H

#include "ThreadSqlQueryInterface.h"
#include "ThreadSqlRes.h"

#include <QObject>
#include <QSqlQuery>
#include <QMap>

class ThreadSqliteObject : public QObject
{
    Q_OBJECT
public:
    using ParseSqlQueryFunction = std::function<int(QSqlQuery const &query)>;
public:
    explicit ThreadSqliteObject(QObject *parent = nullptr);
    void setPath(const QString &newPath);
    void setConnectionName(const QString &newConnectionName);
signals:
    void execDone(QSharedPointer<ThreadSqlQueryInterface>);
    void closeDone();
public slots:
    void initSqlite();
    void closeSqlite();
    void exec(QString const & sql,QSharedPointer<QVariantMap> values,QSharedPointer<ThreadSqlQueryInterface> interface);
private:
    QString path;
    QString connectionName;
    QSqlDatabase db;
};

#endif // THREADSQLITEOBJECT_H
