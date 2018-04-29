#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}


MainWindow::~MainWindow()
{
    delete ui;

}



void MainWindow::on_pb_new_user_clicked()
{
    ui->stackedWidget_login->setCurrentIndex(1);
}

void MainWindow::check_login(const QString username, const QString password)
{
    db_tables table;
    table.connect();
    table.validateLogin(username,password);

}

void MainWindow::on_pb_login_clicked()
{
    ui->stackedWidget_main->setCurrentIndex(1);
}

void MainWindow::on_pb_sign_up_clicked()
{
    uchar title      = ui->cmb_title->currentIndex();
    QString id         = ui->le_id->text();
    QString department = ui->le_department->text();
    QString fname      = ui->le_name->text();
    QString age        = ui->le_age->text();
    QString email      = ui->le_email->text();
    QString phone      = ui->le_phone->text();
    QString pass       = ui->le_pass->text();
    QString cpass      = ui->le_cpass->text();

    std::unique_ptr<IPerson> person = NewPerson::getPerson(PersonType(title));
    person->addBasicInfo(id.toInt(),fname,age.toInt());
    person->addPhoneEmailDept(email,phone,department);

    db_tables table;
    if( table.connect() != db_tables::DB_SUCCESS) return;
    if(table.create_tables(db_tables::DB_LOGIN) != db_tables::DB_SUCCESS) return;
    if(table.insertUser(fname,pass) != db_tables::DB_SUCCESS);
    table.insertPerson(person);
    table.create_tables(db_tables::DB_PERSON);

}
