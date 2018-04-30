#include "student.h"

Student::Student()
{
  setPerson_type(STUDENT);
}

void Student::addBasicInfo(QString id, QString name, int age)
{
  setId(id);
  setName(name);
  setAge(age);
}

void Student::addPhoneEmailDept(QString email, QString phone,QString dept)
{
  setEmail(email);
  setPhone(phone);
  setDept(dept);
}
