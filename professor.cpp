
#include "professor.h"

Professor::Professor()
{
  setPerson_type(PROFESSOR);
}

void Professor::addBasicInfo(QString id, QString name, int age)
{
    setId(id);
    setName(name);
    setAge(age);
}

void Professor::addPhoneEmailDept(QString email, QString phone, QString dept)
{
    setEmail(email);
    setPhone(phone);
    setDept(dept);
}
