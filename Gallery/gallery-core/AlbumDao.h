#ifndef ALBUMDAO_H
#define ALBUMDAO_H

class QSqlDatabase;

// AlbumDao - Album Data access object
class AlbumDao
{
public:
    AlbumDao(QSqlDatabase& database);
    void init() const;

private:
    QSqlDatabase& m_database;
};

#endif // ALBUMDAO_H
