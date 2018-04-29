#include "iperson.h"

IPerson::IPerson()
{

}

QString IPerson::getDept() const
{
    return m_dept;
}

void IPerson::setDept(const QString &dept)
{
    m_dept = dept;
}
