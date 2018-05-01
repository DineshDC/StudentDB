#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "iperson.h"
#include "course.h"

class Professor : public IPerson
{
public:
    Professor();

    void addBasicInfo(QString id, QString name, int age);
    void addPhoneEmailDept(QString email, QString phone= "",QString dept = "") ;

private:
    QMap<int,Course*>teaching_Courses_list;
};

#endif // PROFESSOR_H
