#ifndef THREADSQLRES_H
#define THREADSQLRES_H

#include "ThreadSqlQueryInterface.h"

#include <QString>
#include <memory>

class ThreadSqlRes
{
public:
    ThreadSqlRes(int code,QString const & info);
public:
    const int code;
    const QString info;
    std::shared_ptr<ThreadSqlQueryInterface> getData() const;
    void setData(const std::shared_ptr<ThreadSqlQueryInterface> &newData);

private:
    std::shared_ptr<ThreadSqlQueryInterface> data;
};

#endif // THREADSQLRES_H
