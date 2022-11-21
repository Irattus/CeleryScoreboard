#include "litesqlmanager.h"

static const QString Table("CeleryTable");

bool QueryExec(QSqlQuery * query)
{
    if(query->exec())
        return true;
    else{
        qDebug()<<"Last error "<<query->lastError();
        return false;
    }
}

LiteSqlManager::~LiteSqlManager()
{
    if (isOpen())
        close();
}

LiteSqlManager::LiteSqlManager(QString const& path)
    : QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))
{
    setDatabaseName(path);
    open();
}

bool LiteSqlManager::celeryFounded(const QString& name)
{
    if(!accountExists(name))
        return false;
    QSqlQuery query;
    query.prepare(QString(R"(UPDATE %1 SET celery = celery + 1 WHERE name = (:name))").arg(Table));
    query.bindValue(":name", name);

    return QueryExec(&query);

}

bool LiteSqlManager::addAccount(const QString& name)
{
   QSqlQuery query;
   if(accountExists(name))
       return true;
   query.prepare(QString(R"(INSERT INTO %1 (name,celery) VALUES (:n,0))").arg(Table));
   query.bindValue(":n", name);
   return QueryExec(&query);

}




bool LiteSqlManager::createTable()
{

    QSqlQuery query;
    query.prepare(QString("CREATE TABLE %1(name TEXT PRIMARY KEY, celery INTEGER);").arg(Table));
    return QueryExec(&query);
}

bool LiteSqlManager::accountExists(const QString& name) const
{
    QSqlQuery checkQuery;
    checkQuery.prepare(QString("SELECT name FROM %1 WHERE name = (:name)").arg(Table));
    checkQuery.bindValue(":name", name);
    if(QueryExec(&checkQuery))
        return checkQuery.next();
    else
        return false;
}

bool LiteSqlManager::removeAllAccounts()
{
    QSqlQuery removeQuery;
    removeQuery.prepare(QString("DELETE FROM %1").arg(Table));

    return QueryExec(&removeQuery);
}

bool LiteSqlManager::removeAccount(const QString& name)
{
    if (!accountExists(name))
        return true;
    QSqlQuery queryDelete;
    queryDelete.prepare(QString("DELETE FROM %1 WHERE name = (:name)").arg(Table));
    queryDelete.bindValue(":name", name);
    return QueryExec(&queryDelete);
}


