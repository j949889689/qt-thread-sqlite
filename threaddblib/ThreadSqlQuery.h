#ifndef THREADSQLQUERY_H
#define THREADSQLQUERY_H
#include "ThreadSqlQueryInterface.h"

#include <QList>
#include <QSqlQuery>
#include <functional>
#include <QDebug>

template<typename T>
class ThreadSqlQuery : public ThreadSqlQueryInterface
{
public:
    inline void parseQuery(QSqlQuery & query)override final{
        if(parseQueryFunction){
            parseQueryFunction(query,collection);
        }
    };
    inline void dealQuery()override final{
        if(dealEntityFunction){
            dealEntityFunction(collection);
        }
    };
    T collection;
    std::function<void(T const &)> dealEntityFunction;
    std::function<void(QSqlQuery &,T &)> parseQueryFunction;
};

#endif // THREADSQLQUERY_H
