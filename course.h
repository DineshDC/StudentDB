#ifndef COURSE_H
#define COURSE_H

#include <QWidget>
#include <memory>

namespace Ui {
class Course;
}

class Course : public QWidget
{
    Q_OBJECT

public:
    explicit Course(QWidget *parent = 0);
    Course(int courseId,QString course_name,QString department, QString professorName,QString prerequisite,QWidget *parent = 0);
    ~Course();

    static std::unique_ptr<Course> makeCourse(int courseId,QString course_name,QString department, QString professorName,QString prerequisite );
    int course_id() const;
    void setCourse_id(int course_id);

    QString course_name() const;
    void setCourse_name(const QString &course_name);

    QString department() const;
    void setDepartment(const QString &department);

    QString prerequisites() const;
    void setPrerequisites(const QString &prerequisites);

    QString professor_name() const;
    void setProfessor_name(const QString &professor_name);

private:

    int         m_course_id;
    QString m_course_name;
    QString m_department;
    QString m_professor_name;
    QString m_prerequisites;

    Ui::Course *ui;
};

#endif // COURSE_H
