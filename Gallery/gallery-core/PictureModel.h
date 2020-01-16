#ifndef PICTUREMODEL_H
#define PICTUREMODEL_H

#include <memory>
#include <vector>

#include <QAbstractListModel>

#include "gallery-core_global.h"
#include "Picture.h"

class Album;
class DatabaseManager;
class AlbumModel;

class GALLERYCORESHARED_EXPORT PictureModel : public QAbstractListModel
{
public:

    enum PictureRole {
        FilePathRole = Qt::UserRole + 1
    };

    PictureModel(const AlbumModel& albumModel, QObject* parent = nullptr);

    QModelIndex addPicture(const Picture& picture);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    void setAlbumId(int albumId);
    void clearAlbum();

public slots:
    void deletePicturesForAlbum();

private:
    void loadPictures(int albumId);
    bool isIndexValid(const QModelIndex& index) const;

private:
    DatabaseManager& m_db;
    int m_albumId;
    std::unique_ptr<std::vector<std::unique_ptr<Picture>>> m_pictures;
};

#endif // PICTUREMODEL_H
