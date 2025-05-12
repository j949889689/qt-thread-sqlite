#include "ThreadSqlRes.h"

ThreadSqlRes::ThreadSqlRes(int code, const QString &info)
    :code(code)
    ,info(info)
{

}

std::shared_ptr<ThreadSqlQueryInterface> ThreadSqlRes::getData() const
{
    return data;
}

void ThreadSqlRes::setData(const std::shared_ptr<ThreadSqlQueryInterface> &newData)
{
    data = newData;
}
