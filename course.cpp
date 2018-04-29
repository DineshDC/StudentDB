#include "course.h"
#include "ui_course.h"

Course::Course(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Course)
{
    ui->setupUi(this);
}

Course::Course(int courseId, QString course_name, QString department, QString professorName, QString prerequisite, QWidget *parent)
{
   m_course_id = courseId;
   m_course_name = course_name;
   m_department = department;
   m_professor_name = professorName;
   m_prerequisites = prerequisite;
}

Course::~Course()
{
    delete ui;
}

int Course::course_id() const
{
    return m_course_id;
}

void Course::setCourse_id(int course_id)
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
