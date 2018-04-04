#include "Picture.h"

Picture::Picture(const QString &filePath)
    : Picture(QUrl::fromLocalFile(filePath))
{

}

Picture::Picture(const QUrl &fileUrl)
    : m_id(-1), m_albumId(-1), m_fileUrl(fileUrl)
{

}

int Picture::id() const
{
    return m_id;
}

void Picture::setId(int id)
{
    m_id = id;
}

int Picture::albumId() const
{
    return m_albumId;
}

void Picture::setAlbumId(int albumId)
{
    m_albumId = albumId;
}

QUrl Picture::fileUrl() const
{
    return m_fileUrl;
}

void Picture::setFileUrl(const QUrl &fileUrl)
{
    m_fileUrl = fileUrl;
}
