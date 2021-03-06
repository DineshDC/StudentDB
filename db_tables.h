#ifndef DB_TABLES_H
#define DB_TABLES_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <memory>
#include "iperson.h"
#include "course.h"
#include <QDebug>
#include <QSqlRecord>

class db_tables
{
public:
    enum valid_error_n_values {
        DB_TABLE_AVAILABLE = -6,
        DB_INVALID_QUERY = -5,
        DB_INVALID = -4,
        DB_INVALID_USER = -3,
        DB_CONNECTION_AVAILABLE = -2,
        DB_NOT_OPEN = -1,
        DB_SUCCESS  =  0,
        DB_SIGN_UP    = 1,//table type from here
        DB_PERSON  = 2,
        DB_COURSE = 3

    };
    db_tables();

    short connect(const QString &connectionName, const QString &db_type = "QSQLITE",
                  const QString &hostname = "localhost", const QString &db_name = "person_db",
                  const QString &username = "admin", const QString password = "admin@123");

    void disconnect();

    short create_tables(uchar table_type);
    short validateLogin(const QString &username, const QString &password);

    short insertUser(const QString &username, const QString &password);
    short insertPerson(const std::unique_ptr<IPerson> & person);
    void deletePerson(const int Id);
    void insertCourse(const std::unique_ptr<Course> &course);
    void deleteCourse(const int Id);
    short getAll(valid_error_n_values tabletype,const QString& list_wantIt,QStringList &out_getIt);
    QString getTableName(valid_error_n_values tabletype);

    bool isConnected();
    QSqlDatabase getDB() {return m_db;}
private:
    QString m_tempQuery;

    QSqlDatabase m_db;
    QString m_connectionName = "person";
};

#endif // DB_TABLES_H
