#include "AlbumDao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>

AlbumDao::AlbumDao(QSqlDatabase &database)
    : m_database(database)
{

}

void AlbumDao::init() const
{
    if ( !m_database.tables().contains("albums") )
    {
        QSqlQuery query(m_database);
        query.exec("CREATE TABLE albums (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
    }
}
