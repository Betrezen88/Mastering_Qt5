#ifndef ALBUMDAO_H
#define ALBUMDAO_H

#include <QVector>

class Album;
class QSqlDatabase;

// AlbumDao - Album Data access object
class AlbumDao
{
public:
    AlbumDao(QSqlDatabase& database);
    void init() const;
    void addAlbum(Album& album) const;
    void updateAlbum(const Album& album) const;
    void removeAlbum(int id) const;
    QVector<Album*> albums() const;

private:
    QSqlDatabase& m_database;
};

#endif // ALBUMDAO_H
