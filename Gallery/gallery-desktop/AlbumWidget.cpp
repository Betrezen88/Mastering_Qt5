#include "AlbumWidget.h"
#include "ui_AlbumWidget.h"

#include <QInputDialog>
#include <QFileDialog>

#include "AlbumModel.h"
#include "PictureModel.h"
#include "ThumbnailProxyModel.h"

AlbumWidget::AlbumWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumWidget)
{
    ui->setupUi(this);
    clearUi();

    ui->thumbnailListView->setSpacing(5);
    ui->thumbnailListView->setResizeMode(QListView::Adjust);
    ui->thumbnailListView->setFlow(QListView::LeftToRight);
    ui->thumbnailListView->setWrapping(true);

    connect(ui->thumbnailListView, &QListView::doubleClicked,
            this, &AlbumWidget::pictureActivated);
    connect(ui->deleteBtn, &QPushButton::clicked,
            this, &AlbumWidget::deleteAlbum);
    connect(ui->editBtn, &QPushButton::clicked,
            this, &AlbumWidget::editAlbum);
    connect(ui->addPictureBtn, &QPushButton::clicked,
            this, &AlbumWidget::addPicture);
}

AlbumWidget::~AlbumWidget()
{
    delete ui;
}

void AlbumWidget::setAlbumModel(AlbumModel *albumModel)
{
    m_albumModel = albumModel;
    connect(m_albumModel, &QAbstractItemModel::dataChanged,
            [this](const QModelIndex &topLeft){
        if (topLeft == m_albumSelectionModel->currentIndex())
            loadAlbum(topLeft);
    });
}

void AlbumWidget::setAlbumSelectionModel(QItemSelectionModel *albumSelectionModel)
{
    m_albumSelectionModel = albumSelectionModel;
    connect(m_albumSelectionModel, &QItemSelectionModel::selectionChanged,
            [this](const QItemSelection &selected) {
        if (selected.isEmpty()) {
            clearUi();
            return;
        }
        loadAlbum(selected.indexes().first());
    });
}

void AlbumWidget::setPictureModel(ThumbnailProxyModel *pictureModel)
{
    m_pictureModel = pictureModel;
    ui->thumbnailListView->setModel(m_pictureModel);
}

void AlbumWidget::setPictureSelectionModel(QItemSelectionModel *selectionModel)
{
    ui->thumbnailListView->setSelectionModel(selectionModel);
}

void AlbumWidget::deleteAlbum()
{
    if (m_albumSelectionModel->selectedIndexes().isEmpty())
        return;

    int row = m_albumSelectionModel->currentIndex().row();
    m_albumModel->removeRow(row);

    QModelIndex previousModelIndex = m_albumModel->index(row-1, 0);
    if (previousModelIndex.isValid()) {
        m_albumSelectionModel->setCurrentIndex(
                    previousModelIndex,
                    QItemSelectionModel::SelectCurrent);
        return;
    }

    QModelIndex nextModelIndex = m_albumModel->index(row, 0);
    if (nextModelIndex.isValid()) {
        m_albumSelectionModel->setCurrentIndex(
                    nextModelIndex,
                    QItemSelectionModel::SelectCurrent);
        return;
    }
}

void AlbumWidget::editAlbum()
{
    if (m_albumSelectionModel->selectedIndexes().isEmpty())
        return;

    QModelIndex currentAlbumIndex = m_albumSelectionModel->selectedIndexes().first();
    QString oldAlbumName = m_albumModel->data(currentAlbumIndex, AlbumModel::NameRole).toString();

    bool ok;
    QString newName = QInputDialog::getText(this,
                                            "Album's name",
                                            "Change Album name",
                                            QLineEdit::Normal,
                                            oldAlbumName,
                                            &ok);
    if (ok && !newName.isEmpty()){
        m_albumModel->setData(currentAlbumIndex,
                              newName,
                              AlbumModel::NameRole);
    }
}

void AlbumWidget::addPicture()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(
                this,
                "Add pictures",
                QDir::homePath(),
                "Picture files (*.jpg, *.png)");

    if (!fileNames.isEmpty()) {
        QModelIndex lastModelIndex;
        for (auto fileName: fileNames) {
            Picture picture{fileName};
            lastModelIndex = m_pictureModel->pictureModel()->addPicture(picture);
        }
        ui->thumbnailListView->setCurrentIndex(lastModelIndex);
    }
}

void AlbumWidget::clearUi()
{
    ui->albumName->setText("");
    ui->deleteBtn->setVisible(false);
    ui->editBtn->setVisible(false);
    ui->addPictureBtn->setVisible(false);
}

void AlbumWidget::loadAlbum(const QModelIndex &albumIndex)
{
    m_pictureModel->pictureModel()->setAlbumId(m_albumModel->data(albumIndex, AlbumModel::IdRole).toInt());
    ui->albumName->setText(m_albumModel->data(albumIndex, Qt::DisplayRole).toString());
    ui->deleteBtn->setVisible(true);
    ui->editBtn->setVisible(true);
    ui->addPictureBtn->setVisible(true);
}
