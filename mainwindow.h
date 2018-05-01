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
        MW_EMAIL_INVALID = -10,
        MW_EMAIL_PRESENT = -9,
        MW_ID_PRESENT = -8,
        MW_FAILED = -7,
        MW_INVALID_USER_PASS = -6,
        MW_PASS_CPASS_NOT_MATCH = -5,
        MW_CPASS_INVALID = -4,
        MW_PASS_INVALID = -3,
        MW_DEPT_INVALID = -3,
        MW_NAME_INVALID = -2,
        MW_ID_INVALID = -1,
        MW_SUCCESS = 0,
        MW_MSG_ABOUT = 1,
        MW_MSG_INFO  = 2,
        MW_MSG_WARN  = 3,
        MW_MSG_ERROR  = 4,
    };


    QMap<int,QString > info = {
        {-10, "Enter email id"},
        {-9,"Email id already available"},
        {-8,"ID already available"},
        {-7,"Failed"},
        {-6,"Invalid username or password"},
        {-5,"Confirm password does not match"},
        {-4,"Enter confirm password "},
        {-3,"Enter password"},
        {-2,"Enter Department"},
        {-1,"Enter id"},
    };


    QMenu *menu;
    std::unique_ptr<IPerson> person;


    int validateContent();

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
