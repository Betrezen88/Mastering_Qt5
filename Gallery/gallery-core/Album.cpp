#include "Album.h"

Album::Album(const QString &name)
    : m_id(-1), m_name(name)
{

}

int Album::id() const
{
    return m_id;
}

void Album::setId(int id)
{
    m_id = id;
}

QString Album::name() const
{
    return m_name;
}

void Album::setName(const QString &name)
{
    m_name = name;
}
