#include "PictureModel.h"

#include "AlbumModel.h"
#include "DatabaseManager.h"

PictureModel::PictureModel(const AlbumModel &albumModel, QObject *parent)
    : QAbstractListModel(parent),
      m_db(DatabaseManager::instance()),
      m_albumId(-1),
      m_pictures(new std::vector<std::unique_ptr<Picture>>())
{
    connect(&albumModel, &AlbumModel::rowsRemoved, this, &PictureModel::deletePicturesForAlbum);
}

QModelIndex PictureModel::addPicture(const Picture &picture)
{
    int rowIndex = rowCount();
    beginInsertRows( QModelIndex(), rowIndex, rowIndex );
    std::unique_ptr<Picture> newPicture(new Picture(picture));
    m_db.pictureDao().addPictureInAlbum(m_albumId, *newPicture);
    m_pictures->push_back( std::move(newPicture) );
    endInsertRows();
    return index(rowIndex, 0);
}

int PictureModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_pictures->size();
}

QVariant PictureModel::data(const QModelIndex &index, int role) const
{
    if ( !isIndexValid(index) )
        return QVariant();

    const Picture& picture = *m_pictures->at( index.row() );

    switch (role) {
    case PictureRole::FilePathRole:
        return picture.fileUrl();
        break;
    default:
        return QVariant();
        break;
    }
}

bool PictureModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if( (row < 0) || (row >= rowCount()) || (count < 0) || ((row + count) > rowCount()) )
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while ( --countLeft )
    {
        const Picture& picture = *m_pictures->at( row + countLeft );
        m_db.pictureDao().removePicture( picture.id() );
    }
    m_pictures->erase( m_pictures->begin() + row, m_pictures->begin() + row + count );
    endRemoveRows();
    return true;
}

void PictureModel::setAlbumId(int albumId)
{
    beginResetModel();
    m_albumId = albumId;
    loadPictures(m_albumId);
    endResetModel();
}

void PictureModel::clearAlbum()
{

}

void PictureModel::deletePicturesForAlbum()
{
    m_db.pictureDao().removePictureForAlbum( m_albumId );
    m_pictures.reset( new std::vector<std::unique_ptr<Picture>>() );
}

void PictureModel::loadPictures(int albumId)
{
    if ( albumId <= 0 )
    {
        m_pictures.reset( new std::vector<std::unique_ptr<Picture>>() );
        return;
    }
    m_pictures = m_db.pictureDao().picturesForAlbum( albumId );
}

bool PictureModel::isIndexValid(const QModelIndex &index) const
{
    return ((index.row() > 0) && (index.row() < static_cast<int>(m_pictures->size())));
}
