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

PictureDao DatabaseManager::pictureDao() const
{
    return m_pictureDao;
}

DatabaseManager::DatabaseManager(const QString &path)
    : m_database(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
      m_albumDao(*m_database),
      m_pictureDao(*m_database)
{
    m_database->setDatabaseName(path);
    m_database->open();

    m_albumDao.init();
    m_pictureDao.init();
}
