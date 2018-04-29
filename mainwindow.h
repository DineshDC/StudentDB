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
#include "datatable.h"
namespace Ui {
class MainWindow;
}


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


    QMenu *menu;
    std::unique_ptr<IPerson> person;
private slots:
    void on_pb_new_user_clicked();

    void check_login(const QString username, const QString password);
    void on_pb_login_clicked();


    void on_pb_sign_up_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
