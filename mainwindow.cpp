#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    table = std::make_unique<db_tables>();
    table->connect("db_conn_login");

    thread = new QThread();
    task = new Task(this);
    connect( thread, SIGNAL(started()), task, SLOT(fetchUsers()) );
   // connect( thread, SIGNAL(started()), task, SLOT(fetchCourses()) );


    task->moveToThread(thread);
    thread->start();
}


MainWindow::~MainWindow()
{
    delete ui;

}

int MainWindow::validateContent()
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
    auto it = m_map_users.find(id);

    if(it.key() == id ) return MW_ID_PRESENT;
    if(it.value() == email) return MW_EMAIL_PRESENT;

}




void MainWindow::addCoursesForTest()
{

    short ret =  0;
    ret = table->create_tables(db_tables::DB_COURSE);

    table->insertCourse( Course::makeCourse("1","c++","cs","dd","c"));
    table->insertCourse(Course::makeCourse("2","Advance c++","cs","dd","c"));
    table->insertCourse(Course::makeCourse("3","Java","cs","dd","c"));
    table->insertCourse(Course::makeCourse("4","Advance Java","cs","dd","c,& OOPS"));

    model = new QSqlRelationalTableModel(ui->tableView_Crs_Avail,table->getDB());

    model->setTable("courses");

    model->setHeaderData(model->fieldIndex("id"),Qt::Horizontal,"ID");
    model->setHeaderData(model->fieldIndex("coursename"),Qt::Horizontal,"Course Name");
    model->setHeaderData(model->fieldIndex("department"),Qt::Horizontal,"Department");
    model->setHeaderData(model->fieldIndex("professor"),Qt::Horizontal,"Professor");
    model->setHeaderData(model->fieldIndex("prerequisite"),Qt::Horizontal,"Prerequisite");


    if(!model->select())
    {
        model->lastError();
        return;
    }

    ui->tableView_Crs_Avail->setModel(model);
    ui->tableView_Crs_Avail->setColumnHidden(model->fieldIndex("id"), true);
}




void MainWindow::on_pb_new_user_clicked()
{
    ui->stackedWidget_login->setCurrentIndex(1);
}

short MainWindow::check_login()
{

    short ret = table->validateLogin(ui->le_username->text(),
                                     ui->le_password->text());

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
}

void MainWindow::on_pb_login_clicked()
{
    if( check_login() == MW_FAILED) return;

    ui->stackedWidget_main->setCurrentIndex(1);
    //    addCoursesForTest();

}

void MainWindow::on_pb_sign_up_clicked()
{
    short ret = validateContent();

    if(ret < 0)
    {
        showMessage(MW_MSG_ERROR,info.find(ret).value());
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

    std::unique_ptr<IPerson> person = NewPerson::getPerson(PersonType(title));
    person->addBasicInfo(id,fname,age.toInt());
    person->addPhoneEmailDept(email,phone,department);

    ret = table->create_tables(db_tables::DB_SIGN_UP);
    ret = table->insertUser(email,pass);

    ret = table->create_tables(db_tables::DB_PERSON);
    ret = table->insertPerson(person);


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
    m_ptr->getTable()->getAll(db_tables::DB_PERSON,"id , email",list);

    if(list.isEmpty())
        return;
    for(QString l : list)
    {
        QStringList data = l.split(";");
        m_ptr->getUserMap().insert(data.at(0),data.at(1));
    }
}

void Task::fetchCourses()
{
    qDebug()<<"Fetch Courses";
    QStringList list;
    m_ptr->getTable()->getAll(db_tables::DB_PERSON,"id , coursename",list);

    if(list.isEmpty())
        return;

    for(QString l : list)
    {
        QStringList data = l.split(";");
        m_ptr->getCourseMap().insert(data.at(0),data.at(1));
    }
}

Task::Task(MainWindow *ptr):m_ptr(ptr)
{

}
