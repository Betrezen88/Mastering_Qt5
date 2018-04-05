#include "PictureDao.h"

#include "Picture.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

PictureDao::PictureDao(QSqlDatabase &database)
    : m_database(database)
{

}

void PictureDao::init() const
{
    if ( !m_database.tables().contains("pictures") )
    {
        QSqlQuery query(m_database);
        query.exec( "CREATE TABLE pictures "
                    "(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "album_id INTEGER,"
                    "url TEXT)" );
    }
}

void PictureDao::addPictureInAlbum(int albumId, Picture &picture) const
{
    QSqlQuery query(m_database);
    query.prepare( "INSTER INTO pictures (album_id, url) VALUES (:albumId, :url)" );
    query.bindValue( ":albumId", albumId );
    query.bindValue( ":url", picture.fileUrl() );
    query.exec();
    picture.setId( query.lastInsertId().toInt() );
}

void PictureDao::removePicture(int id) const
{
    QSqlQuery query(m_database);
    query.prepare( "DELETE FROM pictures WHERE id = :id" );
    query.bindValue( ":id", id );
    query.exec();
}

void PictureDao::removePictureForAlbum(int albumId) const
{
    QSqlQuery query(m_database);
    query.prepare( "DELETE FROM pictures WHRE album_id = :albumId" );
    query.bindValue( ":albumId", albumId );
    query.exec();
}

std::unique_ptr<std::vector<std::unique_ptr<Picture>>> PictureDao::picturesForAlbum(int albumId) const
{
    std::unique_ptr<std::vector<std::unique_ptr<Picture>>> list(new std::vector<std::unique_ptr<Picture>>);
    QSqlQuery query(m_database);
    query.prepare( "SELECT * FROM pictures WHERE album_id = :albumId" );
    query.bindValue( ":albumId", albumId );
    query.exec();
    while ( query.next() )
    {
        std::unique_ptr<Picture> picture(new Picture());
        picture->setId( query.value("id").toInt() );
        picture->setAlbumId( query.value("album_id").toInt() );
        picture->setFileUrl( query.value("url").toString() );
        list->push_back( std::move(picture) );
    }
    return list;
}
