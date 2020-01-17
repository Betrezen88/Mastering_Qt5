#ifndef ALBUMWIDGET_H
#define ALBUMWIDGET_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class AlbumWidget;
}

class AlbumModel;
class PictureModel;
class QItemSelectionModel;
class ThumbnailProxyModel;

class AlbumWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumWidget(QWidget *parent = nullptr);
    ~AlbumWidget();

    void setAlbumModel(AlbumModel *albumModel);
    void setAlbumSelectionModel(QItemSelectionModel *albumSelectionModel);
    void setPictureModel(ThumbnailProxyModel *pictureModel);
    void setPictureSelectionModel(QItemSelectionModel *selectionModel);

signals:
    void pictureActivated(const QModelIndex &index);

private slots:
    void deleteAlbum();
    void editAlbum();
    void addPicture();

private:
    void clearUi();
    void loadAlbum(const QModelIndex &albumIndex);

private:
    Ui::AlbumWidget *ui;
    AlbumModel *m_albumModel{nullptr};
    QItemSelectionModel *m_albumSelectionModel{nullptr};
    ThumbnailProxyModel *m_pictureModel{nullptr};
    QItemSelectionModel *m_pictureSelectionModel{nullptr};
};

#endif // ALBUMWIDGET_H
