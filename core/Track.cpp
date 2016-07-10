#include "Track.h"

#include <reader.h>
#include <elements.h>

#include <QByteArray>

#include <istream>

namespace Discogs
{

class Track::Private
{
public:
    Private(const QString &title, const QString &duration);

    QString m_title;
    QString m_duration;
};

Track::Private::Private(const QString &title, const QString &duration) :
    m_title(title),
    m_duration(duration)
{
}

Track::Track(const QString &title, const QString &duration) :
    d(new Private(title, duration))
{
}

Track::Track(const Track &other) :
    d(new Private(other.title(), other.duration()))
{
}

Track::~Track()
{
    delete d;
}

Track &Track::operator=(const Track &other)
{
    d->m_title = other.title();
    d->m_duration = other.duration();

    return *this;
}

bool Track::operator==(const Track &other) const
{
    return d->m_title == other.title() && d->m_duration == other.duration();
}

QString Track::title() const
{
    return d->m_title;
}

QString Track::duration() const
{
    return  d->m_duration;
}

}
