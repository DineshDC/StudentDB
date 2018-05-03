#include "iperson.h"

IPerson::IPerson()
{

}

IPerson &IPerson::operator =(const IPerson &per)
{
    setId(per.getId());
    setName(per.getName());
    setAge(per.getAge());
    setDept(per.getDept());
    setEmail(per.getEmail());
    setPhone(per.getPhone());
    setPerson_type(per.getPerson_type());
}

QString IPerson::getDept() const
{
    return m_dept;
}

void IPerson::setDept(const QString &dept)
{
    m_dept = dept;
}
