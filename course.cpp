#include "course.h"
#include "ui_course.h"

Course::Course(QWidget *parent) :
    QWidget(parent)/*,
    ui(new Ui::Course)*/
{
    //ui->setupUi(this);
}

Course::Course(QString courseId, QString course_name, QString department, QString professorName, QString prerequisite,QString description ,QWidget *parent)
{
   m_course_id      = courseId;
   m_course_name    = course_name;
   m_department     = department;
   m_professor_name = professorName;
   m_prerequisites  = prerequisite;
   m_description    = description;

}

Course::~Course()
{
   // delete ui;
}

std::unique_ptr<Course> Course::makeCourse(QString courseId, QString course_name, QString department, QString professorName, QString prerequisite, QString description)
{
    return std::make_unique<Course>(courseId,course_name,department,professorName,prerequisite,description);
}

QString Course::course_id() const
{
    return m_course_id;
}

void Course::setCourse_id(QString course_id)
{
    m_course_id = course_id;
}

QString Course::course_name() const
{
    return m_course_name;
}

void Course::setCourse_name(const QString &course_name)
{
    m_course_name = course_name;
}

QString Course::department() const
{
    return m_department;
}

void Course::setDepartment(const QString &department)
{
    m_department = department;
}

QString Course::prerequisites() const
{
    return m_prerequisites;
}

void Course::setPrerequisites(const QString &prerequisites)
{
    m_prerequisites = prerequisites;
}

QString Course::professor_name() const
{
    return m_professor_name;
}

void Course::setProfessor_name(const QString &professor_name)
{
    m_professor_name = professor_name;
}

QString Course::description() const
{
    return m_description;
}

void Course::setDescription(const QString &description)
{
    m_description = description;
}
