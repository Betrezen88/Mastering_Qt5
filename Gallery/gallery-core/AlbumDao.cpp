#include "AlbumDao.h"

#include "Album.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

AlbumDao::AlbumDao(QSqlDatabase &database)
    : m_database(database)
{

}

void AlbumDao::init() const
{
    if ( !m_database.tables().contains("albums") )
    {
        QSqlQuery query( m_database );
        query.exec( "CREATE TABLE albums (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)" );
    }
}

void AlbumDao::addAlbum(Album &album) const
{
    QSqlQuery query( m_database );
    query.prepare( "INSERT INTO albums (name) VALUE (:name)" );
    query.bindValue( ":name", album.name() );
    query.exec();
    album.setId( query.lastInsertId().toInt() );
}

void AlbumDao::updateAlbum(const Album &album) const
{
    QSqlQuery query( m_database );
    query.prepare( "UPDATE albums SET name = :name" );
    query.bindValue( ":name", album.name() );
    query.exec();
}

void AlbumDao::removeAlbum(int id) const
{
    QSqlQuery query( m_database );
    query.prepare( "DELETE FROM albums WHERE id = :id" );
    query.bindValue( ":id", id );
    query.exec();
}

std::unique_ptr<std::vector<std::unique_ptr<Album>>> AlbumDao::albums() const
{
    QSqlQuery query( "SELECT * FROM albums", m_database );
    query.exec();
    std::unique_ptr<std::vector<std::unique_ptr<Album>>> list(new std::vector<std::unique_ptr<Album>>);
    while ( query.next() )
    {
        std::unique_ptr<Album> album(new Album());
        album->setId( query.value("id").toInt() );
        album->setName( query.value("name").toString() );
        list->push_back( std::move(album) );
    }
    return list;
}
