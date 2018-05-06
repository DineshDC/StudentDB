#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();

    ui->stackedWidget_login->setCurrentIndex(0);
    ui->stackedWidget_main->setCurrentIndex(0);

    ui->pb_completed->hide();
}


MainWindow::~MainWindow()
{
    delete ui;

}

int MainWindow::validateSignUpContent()
{
    auto id = ui->le_id->text();
    auto email = ui->le_email->text();

    if(id.isEmpty()) return MW_ID_INVALID;

    if(ui->le_name->text().isEmpty()) return MW_NAME_INVALID;

    if(ui->le_department->text().isEmpty()) return MW_DEPT_INVALID;

    if(ui->le_pass->text().isEmpty()) return MW_PASS_INVALID;

    if(ui->le_cpass->text().isEmpty()) return MW_CPASS_INVALID;

    if(ui->le_pass->text() != ui->le_cpass->text()) return MW_PASS_CPASS_NOT_MATCH;

    if(email.isEmpty()) return MW_EMAIL_INVALID;

    if(m_map_users.isEmpty()) return MW_SUCCESS;

    QMap<QString, QString>::iterator i = m_map_users.find("plenty");
    if(i == m_map_users.end()) return MW_SUCCESS;
    if(i.key() == id ) return MW_ID_PRESENT;
    if(i.value() == email) return MW_EMAIL_PRESENT;

}

int MainWindow::validateCourseContent()
{
    auto id = ui->le_course_id->text();
    auto course = ui->le_course_title->text();


    if(id.isEmpty()) return MW_ID_INVALID;

    if(ui->le_course_title->text().isEmpty()) return MW_COURSE_TITLE_INVALID;

    if(ui->le_course_dept_name->text().isEmpty()) return MW_DEPT_INVALID;

    if(ui->le_professor_name->text().isEmpty()) return MW_PROF_NAME_INVALID;

    if(m_map_courses.isEmpty()) return MW_SUCCESS;
    QMap<QString, QString>::iterator it = m_map_courses.find(id);
    if(it == m_map_courses.end()) return MW_SUCCESS;
    if(it.key() == id ) return MW_ID_PRESENT;
    if(it.value() == course) return MW_COURSE_PRESENT;
}




void MainWindow::addCourses()
{

    short ret =  0;

    QStringList list;
    table->getAll(db_tables::DB_COURSE,"*",list);

    if(list.isEmpty())
        return;

    QStringList avail;
    if(m_person->getPerson_type() == STUDENT)
    {
        avail = m_person->getRegCourses();
    }

    ui->tableWidget_Crs_Avail->updateTable(list,avail);
    ui->tableWidget_Crs_Avail->resizeColumnsToContents();

}

void MainWindow::init()
{
    table = std::make_unique<db_tables>();
    table->connect("db_conn_login");

    thread = new QThread();
    task = new Task(this);
    connect( thread, SIGNAL(started()), task, SLOT(fetchUsers()) );
    connect( thread, SIGNAL(started()), task, SLOT(fetchCourses()) );


    ui->stackedWidget_login->setCurrentIndex(0);
    ui->stackedWidget_main->setCurrentIndex(0);
}

void MainWindow::reset()
{
    m_person.reset();
    m_menu_username->deleteLater();
    m_act_logout->deleteLater();
    ui->tableWidget_Crs_Avail->reset();
    ui->tableWidget_MyCrs->reset();
}

void MainWindow::setMyCourseTable(const QStringList &list)
{
    QStringList course_list;
    for(QString l : list)
    {
        auto it = m_course_list.find(l);
        Course cs = it.value();
        course_list.push_back(cs.toString());

    }
    if(course_list.isEmpty()) return;
    ui->tableWidget_MyCrs->updateTable(course_list);
    ui->tableWidget_MyCrs->resizeColumnsToContents();

}




void MainWindow::on_pb_new_user_clicked()
{
    ui->stackedWidget_login->setCurrentIndex(1);
}

short MainWindow::check_login()
{

    if(ui->le_username->text().isEmpty())
    {
        showMessage(MainWindow::MW_MSG_ERROR,"Enter username!");
        return MW_FAILED;
    }

    if(ui->le_password->text().isEmpty())
    {
        showMessage(MainWindow::MW_MSG_ERROR,"Enter password!");
        return MW_FAILED;
    }

    if(m_map_users.isEmpty())
    {
        showMessage(MainWindow::MW_MSG_ERROR,"User not available sign up first!");
        return MW_FAILED;
    }

    QString id;
    short ret = table->validateLogin(ui->le_username->text(),
                                     ui->le_password->text(),id);


    QMap<QString ,std::shared_ptr<IPerson> >::iterator it =  m_person_list.find(id);
    if(it != m_person_list.end())
    {
        m_person = it.value();
        setWindowTitle(m_person->getName());
    }

    if( ret == db_tables::DB_INVALID_QUERY)
    {
        showMessage(MainWindow::MW_MSG_ERROR,"Invalid query");
        return MW_FAILED;
    }
    if( ret == db_tables::DB_INVALID_USER)
    {
        showMessage(MainWindow::MW_MSG_ERROR,"Invalid username or password");
        return MW_FAILED;
    }

    if( ret == db_tables::DB_NOT_TABLE_AVAILABLE)
    {
        showMessage(MainWindow::MW_MSG_ERROR,"Username not available sign up first!");
        return MW_FAILED;
    }
}

void MainWindow::on_pb_login_clicked()
{
//    task->moveToThread(thread);
//    thread->start();

    task->fetchCourses();
    task->fetchUsers();

    if( check_login() == MW_FAILED) return;

    task->fetchRegCourses();
    ui->stackedWidget_main->setCurrentIndex(1);

    if(m_person->getPerson_type() == STUDENT)
    {
        setTabText(ADD_COURSE);

    }
    else if(m_person->getPerson_type() == PROFESSOR)
    {
        setTabText(MY_COURSE);

    }
#if LOGIN_TEST
    m_menu_username = new QMenu(m_person->getName());
    m_act_logout = new QAction("Logout");
    m_menu_username->addAction(m_act_logout);
    connect(m_act_logout,SIGNAL(triggered(bool)),this,SLOT(logout_trigger(bool)));
    ui->menuBar->addMenu(m_menu_username);
#endif
    addCourses();

}

void MainWindow::setTabText(TabsType tab)
{
    switch (tab) {
    case COURSE_AVAILABLE:

        break;
    case MY_COURSE:
        ui->tabWidget_Courses->setTabEnabled(MY_COURSE,false);
        ui->tabWidget_Courses->setTabText(MY_COURSE,"");
        ui->tabWidget_Courses->setTabText(ADD_COURSE,"Add Course");
        ui->tabWidget_Courses->setTabEnabled(ADD_COURSE,true);
        ui->pb_enrolled->hide();
        break;
    case ADD_COURSE:
        ui->tabWidget_Courses->setTabEnabled(ADD_COURSE,false);
        ui->tabWidget_Courses->setTabText(ADD_COURSE,"");
        ui->tabWidget_Courses->setTabText(MY_COURSE,"My Courses");
        ui->tabWidget_Courses->setTabEnabled(MY_COURSE,true);
        ui->pb_enrolled->show();
        break;

    }

}

void MainWindow::on_pb_sign_up_clicked()
{
    short ret = validateSignUpContent();

    if(ret < 0)
    {
        showMessage(MW_MSG_ERROR,m_info.find(ret).value());
        return;
    }

    uchar title        = ui->cmb_title->currentIndex();
    QString id         = ui->le_id->text();
    QString department = ui->le_department->text();
    QString fname      = ui->le_name->text();
    QString age        = ui->le_age->text();
    QString email      = ui->le_email->text();
    QString phone      = ui->le_phone->text();
    QString pass       = ui->le_pass->text();
    QString cpass      = ui->le_cpass->text();

    m_map_users.insert(id,email);

    {
        std::unique_ptr<IPerson> person = NewPerson::getPerson(PersonType(title));
        person->addBasicInfo(id,fname,age.toInt());
        person->addPhoneEmailDept(email,phone,department);

        ret = table->create_tables(db_tables::DB_SIGN_UP);
        ret = table->insertUser(id,email,pass);

        ret = table->create_tables(db_tables::DB_PERSON);
        ret = table->insertPerson(person);
        std::shared_ptr<IPerson> p = NewPerson::getPerson(PersonType(title));
        p->addBasicInfo(id,fname,age.toInt());
        p->addPhoneEmailDept(email,phone,department);
        p->setPerson_type(PersonType(title));
        m_person_list.insert(id,p);
    }


}

void MainWindow::showMessage(MainWindow::valid_invalid msg,QString text)
{
    switch (msg) {
    case MainWindow::MW_MSG_ABOUT:
        QMessageBox::about(this,"About",text);
        break;
    case MainWindow::MW_MSG_INFO:
        QMessageBox::information(this,"Information",text,QMessageBox::Ok );
        break;
    case MainWindow::MW_MSG_WARN:
        QMessageBox::warning(this,"Warning",text,QMessageBox::Ok);
        break;
    case MainWindow::MW_MSG_ERROR:
        QMessageBox::critical(this,"Error",text,QMessageBox::Ok);
        break;
    default:
        QMessageBox::critical(this,"Error",text);
        break;
    }
}

void MainWindow::on_pb_cancel_up_clicked()
{
    ui->stackedWidget_login->setCurrentIndex(0);
}

void Task::fetchUsers()
{
    qDebug()<<"Fetch User";
    QStringList list;
    m_ptr->getTable()->getAll(db_tables::DB_PERSON,"*",list);

    if(list.isEmpty())
        return;
    for(QString l : list)
    {
        QStringList data = l.split(";");
        PersonType pType = PersonType(data.at(data.count() - 1).toInt());

        std::unique_ptr<IPerson> person = NewPerson::getPerson(pType);
        person->setPerson_type(pType);

        person->addBasicInfo(data.at(0),data.at(1),data.at(2).toInt());
        person->addPhoneEmailDept(data.at(3),data.at(4));
        m_ptr->m_person_list.insert(data.at(0),std::move(person));

        m_ptr->getUserMap().insert(data.at(0),data.at(1));
    }
}

void Task::fetchCourses()
{
    qDebug()<<"Fetch Courses";
    QStringList list;
    m_ptr->getTable()->getAll(db_tables::DB_COURSE,"*",list);

    if(list.isEmpty())
        return;

    for(QString l : list)
    {
        QStringList data = l.split(";");
        Course course(data.at(0), data.at(1), data.at(2), data.at(3), data.at(4), data.at(5));
        m_ptr->m_course_list.insert(data.at(0),course);
    }
}

void Task::fetchRegCourses()
{
    qDebug()<<"Fetch Req Courses";

    if(m_ptr->m_person != nullptr)
    {
        QStringList list;
        QString id = m_ptr->m_person->getId();
        m_ptr->getTable()->getRegCourse(db_tables::DB_REG_COURSE,id,list);

        if(list.isEmpty())
            return;

        m_ptr->setMyCourseTable(list);
        m_ptr->m_person->setRegCourses(list);


    }
}

Task::Task(MainWindow *ptr):m_ptr(ptr)
{

}

void MainWindow::on_pb_save_course_clicked()
{
    short ret = validateCourseContent();

    if(ret < 0)
    {
        showMessage(MW_MSG_ERROR,m_info.find(ret).value());
        return;
    }
    QString describe           = ui->textEdit_desciption->toPlainText();

    if(describe.count() >140)
    {
        showMessage(MW_MSG_WARN,"Desciption can enter upto 140 character");
    }

    QString course_title      = ui->le_course_title->text();
    QString course_id         = ui->le_course_id->text();
    QString department        = ui->le_course_dept_name->text();
    QString prof_name         = ui->le_professor_name->text();
    QString prerquisite       = ui->le_prerequires->text();


    std::unique_ptr<Course> course = Course::makeCourse(course_id,course_title,department,prof_name,prerquisite,describe);

    ret = table->create_tables(db_tables::DB_COURSE);
    ret = table->insertCourse(course);

    m_map_courses.insert(course_id,course_title);
    addCourses();
}

void MainWindow::on_pb_enrolled_clicked()
{
    QStringList list = ui->tableWidget_Crs_Avail->getSelection();
    short ret = table->create_tables(db_tables::DB_REG_COURSE);
    for(auto l : list)
        ret = table->insertRegisterCourse(m_person->getId(),l);

    task->fetchRegCourses();
}

void MainWindow::logout_trigger(bool)
{
    ui->stackedWidget_main->setCurrentIndex(0);
    ui->stackedWidget_login->setCurrentIndex(0);
    reset();
}
