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

private:

    QMap<int,Course*>enrolled_Courses_list;
};

#endif // STUDENT_H
