#ifndef STUDENTQUERY_H
#define STUDENTQUERY_H

#include "threaddblib/ThreadSqlQuery.h"
#include "Student.h"
#include <QList>
class StudentQuery
{
public:
    StudentQuery();
    void static parseQueryFunction(QSqlQuery & query,QList<Student> & students);
public:
    void getAllStudent(std::function<void(QList<Student>const&)> const & fn);
    void insertStudent(Student const & student);
private:
    ThreadSqlQuery<QList<Student>> query;
};

#endif // STUDENTQUERY_H
