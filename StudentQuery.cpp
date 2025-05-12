#include "StudentQuery.h"
#include <QVariant>
#include <QSharedPointer>
#include "GlobleApp.h"
StudentQuery::StudentQuery()
{
    GlobleApp::getInstance().threadSqlite->exec(" CREATE TABLE IF NOT EXISTS Student ( "
                                                " id INTEGER PRIMARY KEY, "
                                                " name TEXT NOT NULL, "
                                                " age INTEGER NOT NULL, "
                                                " grade TEXT NOT NULL) ");
}

void StudentQuery::parseQueryFunction(QSqlQuery &query, QList<Student> &students)
{
    while(query.next()){
        students.append(Student(query.value(0).toInt(),
                                query.value(1).toString(),
                                query.value(2).toInt(),
                                query.value(3).toString()));
    }
}

void StudentQuery::getAllStudent(const std::function<void (const QList<Student> &)> &fn)
{
    QSharedPointer<ThreadSqlQuery<QList<Student>>> query = QSharedPointer<ThreadSqlQuery<QList<Student>>>(new ThreadSqlQuery<QList<Student>>());
    query->parseQueryFunction = StudentQuery::parseQueryFunction;
    query->dealEntityFunction = fn;
    GlobleApp::getInstance().threadSqlite->exec(" SELECT * FROM Student ",QSharedPointer<QVariantMap>(),query);
}

void StudentQuery::insertStudent(const Student &student)
{
    QSharedPointer<QVariantMap> vars = QSharedPointer<QVariantMap>(new QVariantMap());
    vars->insert(":name",student.getName());
    vars->insert(":age",student.getAge());
    vars->insert(":grade",student.getGrade());
    GlobleApp::getInstance().threadSqlite->exec(" INSERT INTO Student (name, age, grade) VALUES (:name, :age, :grade) ",vars);
}
