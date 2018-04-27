#ifndef COURSE_H
#define COURSE_H

#include <QWidget>

namespace Ui {
class Course;
}

class Course : public QWidget
{
    Q_OBJECT

public:
    explicit Course(QWidget *parent = 0);
    ~Course();

private:
    Ui::Course *ui;
};

#endif // COURSE_H
