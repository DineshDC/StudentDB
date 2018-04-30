#ifndef IPERSON_H
#define IPERSON_H

#include <QApplication>
#include <iostream>
#include <string>




typedef enum _PersonType {
    STUDENT   = 0,
    PROFESSOR = 1
}PersonType;



class IPerson
{
public:
    IPerson();
    virtual void addBasicInfo(QString id,QString name,int age) = 0;
    virtual void addPhoneEmailDept(QString email = "",QString phone= "",QString dept = "") = 0;


    int getAge() const {return m_age;}
    void setAge(int age){m_age = age;}

    QString getId() const {return m_id;}
    void setId(QString id) {m_id = id;}

    QString getName() const {return m_name;}
    void setName(const QString &name){m_name = name;}

    QString getEmail() const {return m_email;}
    void setEmail(const QString &email){m_email = email;}

    QString getPhone() const {return m_phone;}
    void setPhone(const QString &phone){m_phone = phone;}

    uchar getPerson_type() const{return m_person_type;}
    void setPerson_type(const uchar &person_type) {m_person_type = person_type;}


    QString getDept() const;
    void setDept(const QString &dept);

protected:
    QString m_id;
    QString m_name;
    int m_age;
    QString m_email = "";
    QString m_phone= "";
    QString m_dept = "";
    uchar m_person_type = STUDENT;


};




#endif // IPERSON_H
