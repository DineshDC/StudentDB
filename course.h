#ifndef COURSE_H
#define COURSE_H

#include <memory>
#include <QString>

class Course
{

public:
    explicit Course();
    Course(QString courseId, QString course_name, QString department, QString professorName, QString prerequisite, QString description);
    ~Course();

    static std::unique_ptr<Course> makeCourse(QString courseId,QString course_name,QString department, QString professorName,QString prerequisite ,QString description);
    QString course_id() const;
    void setCourse_id(QString course_id);

    QString course_name() const;
    void setCourse_name(const QString &course_name);

    QString department() const;
    void setDepartment(const QString &department);

    QString prerequisites() const;
    void setPrerequisites(const QString &prerequisites);

    QString professor_name() const;
    void setProfessor_name(const QString &professor_name);

    QString description() const;
    void setDescription(const QString &description);

    QString toString();

private:

    QString m_course_id;
    QString m_course_name;
    QString m_department;
    QString m_professor_name;
    QString m_prerequisites;
    QString m_description;

   // Ui::Course *ui;
};

#endif // COURSE_H
