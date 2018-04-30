#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    table = std::make_unique<db_tables>();
    table->connect("db_conn_login");

}


MainWindow::~MainWindow()
{
    delete ui;

}

int MainWindow::validateContent()
{
    if(ui->le_id->text().isEmpty()) return MW_ID_INVALID;

    if(ui->le_name->text().isEmpty()) return MW_NAME_INVALID;

    if(ui->le_department->text().isEmpty()) return MW_DEPT_INVALID;

    if(ui->le_pass->text().isEmpty()) return MW_PASS_INVALID;

    if(ui->le_cpass->text().isEmpty()) return MW_CPASS_INVALID;

    if(ui->le_pass->text() != ui->le_cpass->text()) return MW_PASS_CPASS_NOT_MATCH;

}




void MainWindow::addCoursesForTest()
{

   short ret =  0;
   ret = table->create_tables(db_tables::DB_COURSE);

   table->insertCourse( Course::makeCourse(1,"c++","cs","dd","c"));
   table->insertCourse(Course::makeCourse(2,"Advance c++","cs","dd","c"));
   table->insertCourse(Course::makeCourse(3,"Java","cs","dd","c"));
   table->insertCourse(Course::makeCourse(4,"Advance Java","cs","dd","c,& OOPS"));

   model = new QSqlRelationalTableModel(ui->tableView_Crs_Avail);
   model->setTable("courses");

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
    addCoursesForTest();
}

void MainWindow::on_pb_sign_up_clicked()
{
    uchar title        = ui->cmb_title->currentIndex();
    QString id         = ui->le_id->text();
    QString department = ui->le_department->text();
    QString fname      = ui->le_name->text();
    QString age        = ui->le_age->text();
    QString email      = ui->le_email->text();
    QString phone      = ui->le_phone->text();
    QString pass       = ui->le_pass->text();
    QString cpass      = ui->le_cpass->text();

    std::unique_ptr<IPerson> person = NewPerson::getPerson(PersonType(title));
    person->addBasicInfo(id,fname,age.toInt());
    person->addPhoneEmailDept(email,phone,department);
    short ret =  0;
    ret = table->create_tables(db_tables::DB_SIGN_UP);
    ret = table->insertUser(fname,pass);

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
        break;
    }
}

void MainWindow::on_pb_cancel_up_clicked()
{
    ui->stackedWidget_login->setCurrentIndex(0);
}
