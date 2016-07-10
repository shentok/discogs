#include "Master.h"

#include <reader.h>
#include <elements.h>

#include <QByteArray>

#include <istream>

namespace Discogs
{

class Master::Private
{
public:
    Private(const QString &name = QString(), const QVector<Track> &tracks = QVector<Track>());

    QString m_title;
    QVector<Track> m_tracks;
};

Master::Private::Private(const QString &title, const QVector<Track> &tracks) :
    m_title(title),
    m_tracks(tracks)
{
}

Master::Master() :
    d(new Private)
{
}

Master::~Master()
{
    delete d;
}

void Master::setJson(const QByteArray &jsonData)
{
    std::istringstream in(jsonData.constData());

    d->m_title.clear();
    d->m_tracks.clear();

    json::Object object;
    json::Reader::Read(object, in);

    const json::String &title = object["title"];
    const json::Array &tracklist = object["tracklist"];

    d->m_title = QString::fromStdString(title.Value());
    for (size_t i = 0; i < tracklist.Size(); ++i) {
        const QString title = QString::fromStdString(json::String(tracklist[i]["title"]).Value());
        const QString duration = QString::fromStdString(json::String(tracklist[i]["duration"]).Value());
        const Track track = Track(title, duration);
        d->m_tracks.append(track);
    }
}

Master &Master::operator=(const Master &other)
{
    d->m_title = other.title();
    d->m_tracks = other.tracks();

    return *this;
}

QString Master::title() const
{
    return d->m_title;
}

QVector<Track> Master::tracks() const
{
    return  d->m_tracks;
}

}
