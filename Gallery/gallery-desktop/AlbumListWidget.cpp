#include "AlbumListWidget.h"
#include "ui_AlbumListWidget.h"

#include <QInputDialog>

#include "AlbumModel.h"

AlbumListWidget::AlbumListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumListWidget)
{
    ui->setupUi(this);
    connect(ui->createAlbumBtn, &QPushButton::clicked,
            this, &AlbumListWidget::createAlbum);
}

AlbumListWidget::~AlbumListWidget()
{
    delete ui;
}

void AlbumListWidget::setModel(AlbumModel *model)
{
    m_albumModel = model;
    ui->albumList->setModel(m_albumModel);
}

void AlbumListWidget::setSelectionModel(QItemSelectionModel *selectionModel)
{
    ui->albumList->setSelectionModel(selectionModel);
}

void AlbumListWidget::createAlbum()
{
    if (!m_albumModel)
        return;

    bool ok;
    QString albumName = QInputDialog::getText(this,
                                              "Create a new Album",
                                              "Choose an name",
                                              QLineEdit::Normal,
                                              "New album",
                                              &ok);

    if (ok && !albumName.isEmpty()) {
        Album album(albumName);
        QModelIndex createIndex = m_albumModel->addAlbum(album);
        ui->albumList->setCurrentIndex(createIndex);
    }
}
