#include "ThreadSqliteObject.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QVariantMap>
#ifdef QT_DEBUG
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>
#endif
ThreadSqliteObject::ThreadSqliteObject(QObject *parent)
    : QObject{parent}
{

}

void ThreadSqliteObject::setPath(const QString &newPath)
{
    path = newPath;
}

void ThreadSqliteObject::setConnectionName(const QString &newConnectionName)
{
    connectionName = newConnectionName;
}

void ThreadSqliteObject::initSqlite()
{
    db = QSqlDatabase::addDatabase("QSQLITE",connectionName);
    db.setDatabaseName(path);
    if (!db.open()) {
        qWarning() << "open database error:" << db.lastError().text();
    }
}

void ThreadSqliteObject::closeSqlite()
{
    db.close();
    emit closeDone();
}

void ThreadSqliteObject::exec(const QString &sql, QSharedPointer<QVariantMap> values, QSharedPointer<ThreadSqlQueryInterface> interface)
{
    QSqlQuery query(db);
    query.prepare(sql);
    if(!values.isNull()){
        QVariantMap::const_iterator i;
        for (i = values->constBegin(); i != values->constEnd(); ++i) {
            query.bindValue(i.key(),i.value());
        }
    }
#ifdef QT_DEBUG
    QString debugInfo;
    QTextStream textStream(&debugInfo);
    textStream<<"exec sql:"<<sql;
    if(!values.isNull()){
        QJsonObject jsonObject = QJsonObject::fromVariantMap(*values);
        QJsonDocument jsonDoc(jsonObject);
        textStream<<", parms: "<<jsonDoc.toJson(QJsonDocument::Compact);
    }
    qDebug()<<debugInfo;
#endif
    if(!query.exec()){
        qWarning()<<"exec sql error:"<<sql<<"   error info:"<<query.lastError().text();
    }
    if(!interface.isNull()){
        interface->parseQuery(query);
        emit execDone(interface);
    }

}


