#include "Student.h"

Student::Student()
{

}

Student::Student(int id, const QString& name, int age, const QString& grade)
    : m_id(id), m_name(name), m_age(age), m_grade(grade) {}

int Student::getId() const {
    return m_id;
}

QString Student::getName() const {
    return m_name;
}

int Student::getAge() const {
    return m_age;
}

QString Student::getGrade() const {
    return m_grade;
}

void Student::setName(const QString& name) {
    m_name = name;
}

void Student::setAge(int age) {
    m_age = age;
}

void Student::setGrade(const QString& grade) {
    m_grade = grade;
}
