#include "db_tables.h"
#include "db_tables.h"
#include "db_tables.h"

db_tables::db_tables()
{
    qDebug() << QSqlDatabase::drivers();
}

short db_tables::connect(const QString &connectionName,const QString &db_type,
                         const QString &hostname, const QString &db_name,
                         const QString &username, const QString password)
{

    m_connectionName = connectionName;

    QSqlDatabase db = m_db.database(m_connectionName);
    if(!db.isValid())
    {
        m_db = QSqlDatabase::addDatabase( db_type,m_connectionName);

        m_db.setHostName( hostname );
        m_db.setDatabaseName(db_name);

        m_db.setUserName(username);
        m_db.setPassword( password);

    }

    if(!m_db.open()) { qDebug()<<"Unable to open connection" ; return DB_NOT_OPEN; }
    else { qDebug() << "connection success" ; return DB_SUCCESS; }



}


void db_tables::disconnect()
{
    m_db.close();
}

short db_tables::create_tables(uchar table_type)
{
    QStringList tables = m_db.tables();

    QSqlQuery query(m_db);
    switch (table_type) {
    case DB_SIGN_UP:
    {
        if (tables.contains("login", Qt::CaseInsensitive)) return DB_TABLE_AVAILABLE;
        query.prepare( "CREATE TABLE IF NOT EXISTS login (key VARCHAR(60) UNIQUE PRIMARY KEY, username VARCHAR(50), password VARCHAR(30))" );
        if( !query.exec() ) { qDebug() << query.lastError(); return DB_INVALID_QUERY; }
        else  { qDebug() << "login table created!"; return DB_SUCCESS; }
        break;
    }
    case DB_PERSON:
    {
        if (tables.contains("persons", Qt::CaseInsensitive)) return DB_TABLE_AVAILABLE;
        query.prepare( "CREATE TABLE IF NOT EXISTS persons (id VARCHAR(30) UNIQUE PRIMARY KEY, fullname VARCHAR(30), age INTEGER, email VARCHAR(50), phone VARCHAR(20), department VARCHAR(80), person_type INTEGER)" );
        if( !query.exec() )  { qDebug() << query.lastError(); return DB_INVALID_QUERY; }
        else  { qDebug() << "Person table created!"; return DB_SUCCESS; }

        break;
    }
    case DB_COURSE:
    {
        if (tables.contains("courses", Qt::CaseInsensitive)) return DB_TABLE_AVAILABLE;
        query.prepare( "CREATE TABLE IF NOT EXISTS courses (id VARCHAR(30) UNIQUE PRIMARY KEY, coursename VARCHAR(30), department VARCHAR(80), professor VARCHAR(50), prerequisite VARCHAR(80), description VARCHAR(140) )" );
        if( !query.exec() ) {  qDebug() << query.lastError(); return DB_INVALID_QUERY; }
        else  { qDebug() << "Course table created!"; return DB_SUCCESS; }
        break;
    }
    case DB_REG_COURSE:
    {
        if (tables.contains("reg_courses", Qt::CaseInsensitive)) return DB_TABLE_AVAILABLE;
        query.prepare( "CREATE TABLE IF NOT EXISTS reg_courses ( course_id VARCHAR(30) UNIQUE PRIMARY KEY, student_id VARCHAR(30) )");
        if( !query.exec() ) {  qDebug() << query.lastError(); return DB_INVALID_QUERY; }
        else  { qDebug() << "Course table created!"; return DB_SUCCESS; }
        break;
    }

    default:
        break;
    }


}

short db_tables::validateLogin(const QString &username, const QString &password, QString &key)
{
    QStringList tables = m_db.tables();
    qDebug()<<tables;
    if (!tables.contains("login", Qt::CaseInsensitive)) return DB_TABLE_AVAILABLE;
    QSqlQuery query(m_db);

    m_tempQuery = "SELECT key,username, password FROM login WHERE username = '" + username + "'";
    //    m_tempQuery = "SELECT * FROM login";
    query.prepare(m_tempQuery);
    if( !query.exec() )
    {
        qDebug() <<m_tempQuery<<"\n"<< query.lastError();
        return DB_INVALID_QUERY;
    }
    else
    {
        /*As we know username will be unique we are using this directly*/
        query.next();
        key  = query.value(0).toString();
        QString user = query.value(1).toString();
        QString pass = query.value(2).toString();


        if(user.isEmpty() || pass.isEmpty()) return DB_INVALID_USER;

        if( (user == username) && (pass == password)) return DB_SUCCESS;
        else return DB_INVALID_USER;

#ifdef TEST
        QSqlRecord rec = query.record();
        int cols = rec.count();
        qDebug()<<"cnt "<<cols;
        QString temp = "";
        while( query.next() )
        {

            for( int c=0; c<cols; c++ )
            {
                //                qDebug()<<"-->"<<query.value(c).toString() + ((c<cols-1)?"\t":"");
                //                users.push_back(query.value(c).toString());
                temp += query.value(c).toString() + ((c<cols-1)?"\t":"");
            }
            qDebug()<<temp;
        }

#endif
    }
}

short db_tables::insertUser(const QString &key,const QString &username, const QString &password)
{
    QSqlQuery query(m_db);
    m_tempQuery  = "INSERT INTO login (key,username,password) VALUES (:key,:username,:password )";

    qDebug()<<m_tempQuery;

    query.prepare( m_tempQuery );
    query.bindValue(":key",key);
    query.bindValue(":username",username);
    query.bindValue(":password",password);

    if( !query.exec() )
    { qDebug() << query.lastError();  return DB_INVALID ; }
    else
    {  qDebug( )<<"User:"<<username <<" inserted into table";return DB_SUCCESS; }
}

short db_tables::insertPerson(const std::unique_ptr<IPerson> & person)
{
    QSqlQuery query(m_db);
    m_tempQuery  = "INSERT INTO persons (id,fullname,age,email,phone,department,person_type) VALUES ( :id, :fullname,"
                   ":age,:email,:phone,:department, :person_type )";
    query.prepare( m_tempQuery );

    query.bindValue(":id",person->getId());
    query.bindValue(":fullname",person->getName()  );
    query.bindValue(":age",person->getAge());
    query.bindValue(":email" ,person->getEmail() );
    query.bindValue(":phone", person->getPhone());
    query.bindValue(":department",person->getDept() );
    query.bindValue(":person_type",person->getPerson_type() );

    if( !query.exec() )
    {  qDebug() << query.lastError();return DB_INVALID ;}
    else
    { qDebug( )<<"Person: "<<person->getName() <<" inserted into table"; return DB_INVALID; }
}

void db_tables::deletePerson(const int Id)
{

}

short db_tables::insertCourse(const std::unique_ptr<Course> & course)
{
    QSqlQuery query(m_db);
    m_tempQuery  = "INSERT INTO courses (id,coursename,department,professor,prerequisite, description) VALUES (:id,:coursename,:department,:professor, :prerequisite, :description)";
    query.prepare( m_tempQuery );
    query.bindValue(":id",           course->course_id());
    query.bindValue(":coursename",   course->course_name());
    query.bindValue(":department",   course->department() );
    query.bindValue(":professor",    course->professor_name() );
    query.bindValue(":prerequisite", course->prerequisites() );
    query.bindValue(":description",  course->description().trimmed() );

    //    const QMap<QString,QVariant> values = query.boundValues();
    //    int paramCount = values.count();
    //    qDebug()<<paramCount;

    if( !query.exec() )
    {
        qDebug() << query.lastError();
        qDebug()<<course->course_id()<<
                  course->course_name()<<
                  course->department()<<
                  course->professor_name() <<
                  course->prerequisites()<<
                  course->description() ;
        return DB_INVALID_QUERY;
    }
    else
    {
        qDebug( )<< course->course_name() <<" inserted into table";
        return DB_SUCCESS;
    }
}

void db_tables::deleteCourse(const int Id)
{

}

short db_tables::insertRegisterCourse(const QString &student_id, const QString &course_id)
{
    QSqlQuery query(m_db);
    m_tempQuery  = "INSERT INTO reg_courses (course_id, student_id) VALUES (:course_id,:student_id)";
    query.prepare( m_tempQuery );
    query.bindValue(":course_id",   course_id  );
    query.bindValue(":student_id",  student_id );

    if( !query.exec() )
    {
        qDebug() << query.lastError();
        return DB_INVALID_QUERY;
    }
    else
    {
        qDebug( )<< course_id <<" inserted into table";
        return DB_SUCCESS;
    }
}

QString db_tables::getTableName(valid_error_n_values tabletype)
{
    QStringList strlist;
    strlist<<"login"<<"persons"<<"courses"<<"reg_courses";
    return strlist.at(tabletype-valid_error_n_values(1));
}

short db_tables::getAll(valid_error_n_values tabletype,const QString& list_wantIt,QStringList &out_getIt)
{
    QStringList tables = m_db.tables();

    QSqlQuery query(m_db);

    QString tablename = getTableName(tabletype);

    if(tabletype == DB_PERSON || tabletype == DB_COURSE || tabletype == DB_SIGN_UP)
        if (!tables.contains(tablename, Qt::CaseInsensitive)) return DB_INVALID;



    qDebug()<<"table"<<tablename;

    m_tempQuery = "SELECT "+ list_wantIt + " FROM " + tablename;

    query.prepare(m_tempQuery);
    if( !query.exec() )
    {
        qDebug() <<m_tempQuery<<"\n"<< query.lastError();
        return DB_INVALID_QUERY;
    }
    else
    {
        QSqlRecord rec = query.record();
        int cols = rec.count();
        qDebug()<<"cnt "<<cols;
        QString temp = "";
        while( query.next() )
        {

            temp = "";
            for( int c=0; c<cols; c++ )
            {
                temp += query.value(c).toString() + ((c<cols-1)?";":"");
            }
            out_getIt.push_back(temp);
        }
    }
}

short db_tables::getRegCourse(valid_error_n_values tabletype, const QString& id,QStringList &out_getIt)
{
    QStringList tables = m_db.tables();

    QSqlQuery query(m_db);

    QString tablename = getTableName(tabletype);

    if(tabletype == DB_PERSON || tabletype == DB_COURSE || tabletype == DB_SIGN_UP)
        if (!tables.contains(tablename, Qt::CaseInsensitive)) return DB_INVALID;
    m_tempQuery = "SELECT course_id FROM reg_courses WHERE student_id = '" + id + "'";

    query.prepare(m_tempQuery);
    if( !query.exec() )
    {
        qDebug() <<m_tempQuery<<"\n"<< query.lastError();
        return DB_INVALID_QUERY;
    }
    else
    {
        QSqlRecord rec = query.record();
        int cols = rec.count();
        QString temp = "";
        while( query.next() )
        {

            temp = "";
            for( int c=0; c<cols; c++ )
            {
                temp += query.value(c).toString() + ((c<cols-1)?";":"");
            }
            qDebug()<<"cnt "<<temp;
            out_getIt.push_back(temp);
        }
    }
}

bool db_tables::isConnected()
{
    return m_db.isOpen();
}
