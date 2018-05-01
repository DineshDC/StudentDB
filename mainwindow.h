#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

#include <memory>

#include "course.h"

#include "student.h"
#include "professor.h"

#include <QLayout>
#include <QTableWidget>
#include <QMap>
#include <QMessageBox>
#include <QSqlRelationalTableModel>
#include <QThread>

#include "datatable.h"
namespace Ui {
class MainWindow;
}

class Task;

class NewPerson{
public:
    static std::unique_ptr<IPerson> getPerson(PersonType person)
    {
        switch (person)
        {
        case STUDENT : return std::make_unique<Student>();
        case PROFESSOR : return std::make_unique<Professor>();
        }
        return NULL;
    }
};




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    enum valid_invalid {

        MW_COURSE_TITLE_INVALID = -14,
        MW_PROF_NAME_INVALID = -13,
        MW_COURSE_PRESENT = -12,
        MW_EMAIL_INVALID = -11,
        MW_EMAIL_PRESENT = -10,
        MW_ID_PRESENT = -9,
        MW_FAILED = -8,
        MW_INVALID_USER_PASS = -7,
        MW_PASS_CPASS_NOT_MATCH = -6,
        MW_CPASS_INVALID = -5,
        MW_PASS_INVALID = -4,
        MW_DEPT_INVALID = -3,
        MW_NAME_INVALID = -2,
        MW_ID_INVALID = -1,
        MW_SUCCESS = 0,
        MW_MSG_ABOUT = 1,
        MW_MSG_INFO  = 2,
        MW_MSG_WARN  = 3,
        MW_MSG_ERROR  = 4,
    };


    QMap<int,QString > m_info = {
        {MW_COURSE_TITLE_INVALID, "Enter course title"},
        {MW_PROF_NAME_INVALID, "Enter professor name"},
        {MW_COURSE_PRESENT, "Course already available"},
        {MW_EMAIL_INVALID, "Enter email id"},
        {MW_EMAIL_PRESENT,"Email id already available"},
        {MW_ID_PRESENT,"ID already available"},
        {MW_FAILED,"Failed"},
        {MW_INVALID_USER_PASS,"Invalid username or password"},
        {MW_PASS_CPASS_NOT_MATCH,"Confirm password does not match"},
        {MW_CPASS_INVALID,"Enter confirm password "},
        {MW_PASS_INVALID,"Enter password"},
        {MW_DEPT_INVALID,"Enter Department"},
        {MW_NAME_INVALID,"Enter name"},
        {MW_ID_INVALID,"Enter id"},
    };


    QMenu *menu;
    std::unique_ptr<IPerson> person;


    int validateSignUpContent();
    int validateCourseContent();

    void addCoursesForTest();

    std::unique_ptr<db_tables>& getTable(){return table;}
    QMap<QString,QString>& getUserMap() {return m_map_users;}
    QMap<QString,QString>& getCourseMap() {return m_map_courses;}
private slots:
    void on_pb_new_user_clicked();

    short check_login();
    void on_pb_login_clicked();


    void on_pb_sign_up_clicked();

    void showMessage(valid_invalid msg, QString text);
    void on_pb_cancel_up_clicked();


    void on_pb_save_course_clicked();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<db_tables> table;

    QThread *thread;
    Task *task;

    QSqlRelationalTableModel *model;

    QMap<QString,QString> m_map_users;
    QMap<QString ,QString> m_map_courses;

};

class Task : public QObject
{
    Q_OBJECT
public:
    Task(MainWindow *ptr);
    ~Task() {}
public slots:
    void fetchUsers();
    void fetchCourses();

private:
    MainWindow *m_ptr;


};
#endif // MAINWINDOW_H
