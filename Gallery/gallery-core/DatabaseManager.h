#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>

#include "AlbumDao.h"

class QSqlDatabase;

const QString DATABASE_FILENAME = "gallery.db";

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();

    AlbumDao albumDao() const;

protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);

private:
    QSqlDatabase* m_database;
    const AlbumDao m_albumDao;
};

#endif // DATABASEMANAGER_H
