#ifndef IPERSON_H
#define IPERSON_H

#include <iostream>
#include <string>
#include <QApplication>

typedef enum _PersonType {
    STUDENT   = 0,
    PROFESSOR = 1
}PersonType;

class IPerson
{
public:
    IPerson(char person_type);
    virtual void addBasicInfo(int id,std::string name,int age) = 0;
    virtual void addPhoneEmail(std::string email = "",std::string phone= "") = 0;

private:
    IPerson* getInstance();

protected:
    int m_id;
    std::string m_name;
    int m_age;
    std::string m_email = "";
    std::string m_phone= "";
    uchar m_person_type = STUDENT;


};

#endif // IPERSON_H
