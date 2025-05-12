#ifndef THREADSQLQUERYINTERFACE_H
#define THREADSQLQUERYINTERFACE_H

class QSqlQuery;
class ThreadSqlQueryInterface
{
public:
    virtual ~ThreadSqlQueryInterface() {}
    virtual void parseQuery(QSqlQuery & query)=0;
    virtual void dealQuery()=0;
};

#endif // THREADSQLQUERYINTERFACE_H
