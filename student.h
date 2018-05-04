#ifndef STUDENT_H
#define STUDENT_H

#include "course.h"
#include "db_tables.h"

#include "iperson.h"

class Student : public IPerson
{
public:
    Student();

    void addBasicInfo(QString id, QString name, int age);
    void addPhoneEmailDept(QString email, QString phone= "", QString dept= "") ;

    void setRegCourses(QStringList list) {m_regCourses = list;}
    QStringList getRegCourses() {return m_regCourses;}
private:

    QStringList m_regCourses;
};

#endif // STUDENT_H
