#include <QCoreApplication>
#include <QSqlDatabase>
#include "threaddblib/ThreadSqlQueryInterface.h"
#include <QSharedPointer>
#include "GlobleApp.h"
#include "StudentQuery.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qRegisterMetaType<QSharedPointer<ThreadSqlQueryInterface>>("QSharedPointer<ThreadSqlQueryInterface>");
    qRegisterMetaType<QSharedPointer<QVariantMap>>("QSharedPointer<QVariantMap>");
    GlobleApp::getInstance().init();

    Student student;
    student.setAge(20);
    student.setGrade("60");
    student.setName("zhang san");

    StudentQuery studentQuery;
    studentQuery.insertStudent(student);
    studentQuery.getAllStudent([](const QList<Student> & infos){
        for(auto & it : infos){
            qDebug()<<"Student{Name:"<<it.getName()<<",Age:"<<it.getAge()<<",Grade:"<<it.getGrade()<<"}";
        }
    });
    GlobleApp::getInstance().threadSqlite->closeExec();
    return a.exec();
}
