#ifndef DISCOGS_ARTIST_H
#define DISCOGS_ARTIST_H

#include <QString>
#include <QUrl>

namespace Discogs
{

class Artist
{
public:
    Artist();

    ~Artist();

    void setJson(const QByteArray &jsonData);

    Artist &operator=(const Artist &other);

    QString name() const;

    QUrl releasesUrl() const;

private:
    class Private;
    Private *const d;
};

}

#endif // DISCOGS_ARTIST_H
