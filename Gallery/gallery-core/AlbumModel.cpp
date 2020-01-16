#include "AlbumModel.h"

AlbumModel::AlbumModel(QObject* parent)
    : QAbstractListModel(parent),\
      m_db(DatabaseManager::instance()),
      m_albums(m_db.albumDao().albums())
{

}

QModelIndex AlbumModel::addAlbum(const Album &album)
{
    int rowIndex = rowCount();
    beginInsertRows( QModelIndex(), rowIndex, rowIndex );
    std::unique_ptr<Album> newAlbum(new Album(album));
    m_db.albumDao().addAlbum(*newAlbum);
    m_albums->push_back( std::move(newAlbum) );
    endInsertRows();
    return index(rowIndex, 0);
}

int AlbumModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_albums->size());
}

QVariant AlbumModel::data(const QModelIndex &index, int role) const
{
    if ( !isIndexValid(index) )
        return QVariant();

    const Album& album = *m_albums->at( index.row() );

    switch (role)
    {
        case Roles::IdRole:
            return album.id();
        case Roles::NameRole:
        case Qt::DisplayRole:
            return album.name();
        default:
            return QVariant();
    }
}

bool AlbumModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if ( !isIndexValid(index) || role != Roles::NameRole )
        return false;

    Album& album = *m_albums->at( index.row() );
    album.setName( value.toString() );
    m_db.albumDao().updateAlbum(album);
    emit dataChanged(index, index);
    return true;
}

bool AlbumModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if ( (row < 0) || (row >= rowCount()) || (count < 0) || ((row + count) > rowCount()) )
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while ( --countLeft )
    {
        const Album& album = *m_albums->at(row + countLeft);
        m_db.albumDao().removeAlbum( album.id() );
    }
    m_albums->erase( m_albums->begin() + row, m_albums->begin() + row + count  );
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> AlbumModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::IdRole] = "id";
    roles[Roles::NameRole] = "name";
    return roles;
}

bool AlbumModel::isIndexValid(const QModelIndex &index) const
{
    return ((index.row() > 0) && (index.row() < static_cast<int>(m_albums->size())));
}
