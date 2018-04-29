#include "db_tables.h"

db_tables::db_tables()
{

}

short db_tables::connect(const QString &db_type, const QString &connectionName,
                         const QString &hostname, const QString &db_name,
                         const QString &username, const QString password)
{
    m_connectionName = connectionName;

    if(m_db.contains(connectionName)) return DB_CONNECTION_AVAILABLE;

    m_db = QSqlDatabase::addDatabase( db_type, connectionName);

    m_db.setHostName( hostname );
    m_db.setDatabaseName(db_name);

    m_db.setUserName(username);
    m_db.setPassword( password);

    if(!m_db.open()) { qDebug()<<"Unable to open connection" ; return DB_NOT_OPEN; }
    else { qDebug() << "connection success" ; return DB_SUCCESS; }
}

short db_tables::create_tables(uchar table_type)
{
    if(m_db.contains(m_connectionName)) return DB_CONNECTION_AVAILABLE;

    switch (table_type) {
    case DB_LOGIN:

        m_query.prepare( "CREATE TABLE IF NOT EXISTS login (key INTEGER UNIQUE PRIMARY KEY, username VARCHAR(30), password VARCHAR(80))" );
        if( !m_query.exec() )  qDebug() << m_query.lastError();
        else  qDebug() << "login table created!";
        break;
    case DB_PERSON:
        m_query.prepare( "CREATE TABLE IF NOT EXISTS persons (id INTEGER UNIQUE PRIMARY KEY, fullname VARCHAR(30), \
                         age INTEGER,email VARCHAR(50), phone VARCHAR(20), person_type INTEGER" );
                         if( !m_query.exec() )  qDebug() << m_query.lastError();
                else  qDebug() << "Person table created!";

        break;

    case DB_COURSE:

        m_query.prepare( "CREATE TABLE IF NOT EXISTS courses (id INTEGER UNIQUE PRIMARY KEY, coursename VARCHAR(30), depatment VARCHAR(80)), \
                         professor VARCHAR(50), prerequisite VARCHAR(150)" );
                         if( !m_query.exec() )  qDebug() << m_query.lastError();
                else  qDebug() << "Course table created!";
        break;
    default:
        break;
    }


}

short db_tables::validateLogin(const QString &username, const QString &password)
{
    if(!m_db.contains(m_connectionName)) return DB_INVALID_USER;

    m_tempQuery = "SELECT username password FROM login WHERE username = '" + username + "'";

    if( !m_query.exec() )
        qDebug() << m_query.lastError();
    else
    {
        qDebug( "Selected!" );

        QSqlRecord rec = m_query.record();

        int cols = rec.count();

        for( int c=0; c<cols; c++ )
            qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );
    }
}

short db_tables::insertUser(const QString &username, const QString &password)
{
    QString key = username+" "+password;
    m_tempQuery  = "INSERT INTO login (key,username,password) VALUES ("
            + key + ","
            + username + ","
            + password + ")";
    m_query.prepare( m_tempQuery );
    if( !m_query.exec() )
    { qDebug() << m_query.lastError();  return DB_INVALID ; }
    else
    {  qDebug( )<<username <<" inserted into table"; return DB_INVALID; }
}

short db_tables::insertPerson(const std::unique_ptr<IPerson> & person)
{
    m_tempQuery  = "INSERT INTO persons (id,fullname,age,email,phone,person_type) VALUES ("
            + QString::number(person->getId()) + ","
            + person->getName()  + ","
            + QString::number(person->getAge() )+ ","
            + person->getEmail() + ","
            + person->getPhone()  + ","
            + QString::number(person->getPerson_type() )+ ")";
    m_query.prepare( m_tempQuery );
    if( !m_query.exec() )
    {  qDebug() << m_query.lastError();return DB_INVALID ;}
    else
    { qDebug( )<<person->getName() <<" inserted into table"; return DB_INVALID; }
}

void db_tables::deletePerson(const int Id)
{

}

void db_tables::insertCourse(const Course &course)
{
    m_tempQuery  = "INSERT INTO courses (id,coursename,department,professor,prerequisite) VALUES ("
            + QString::number(course.course_id())+ ","
            + course.course_name() + ","
            + course.department() +","
            + course.professor_name() + ","
            + course.prerequisites() +  ")";
    m_query.prepare( m_tempQuery );
    if( !m_query.exec() )
        qDebug() << m_query.lastError();
    else
        qDebug( )<< course.course_name() <<" inserted into table";
}

void db_tables::deleteCourse(const int Id)
{

}
