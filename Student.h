#ifndef STUDENT_H
#define STUDENT_H

#include <QString>


class Student {
public:
    Student();
    Student(int id, const QString& name, int age, const QString& grade);

    int getId() const;
    QString getName() const;
    int getAge() const;
    QString getGrade() const;

    void setName(const QString& name);
    void setAge(int age);
    void setGrade(const QString& grade);

private:
    int m_id;
    QString m_name;
    int m_age;
    QString m_grade;
};


#endif // STUDENT_H
