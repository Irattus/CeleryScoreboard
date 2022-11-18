#ifndef LITESQLMANAGER_H
#define LITESQLMANAGER_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class LiteSqlManager : public QSqlDatabase
{
public:
    LiteSqlManager(QString const& path);
    ~LiteSqlManager();
    inline bool loaded()const { return isOpen(); }
    bool createTable();
    bool removeAccount(QString const& name);
    bool addAccount(QString const& name);
    bool accountExists(QString const& name) const;
    bool removeAllAccounts();
    bool celeryFounded(QString const&);
};

#endif // LITESQLMANAGER_H
