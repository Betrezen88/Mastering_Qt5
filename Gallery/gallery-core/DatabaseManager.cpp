#include "DatabaseManager.h"

#include <QSqlDatabase>

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::~DatabaseManager()
{
    m_database->close();
    delete m_database;
}

AlbumDao DatabaseManager::albumDao() const
{
    return m_albumDao;
}

DatabaseManager::DatabaseManager(const QString &path)
    : m_database(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
      m_albumDao(*m_database)
{
    m_database->setDatabaseName(path);
    m_database->open();

    m_albumDao.init();
}
