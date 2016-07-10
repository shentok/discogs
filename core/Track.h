#ifndef DISCOGS_TRACK_H
#define DISCOGS_TRACK_H

#include <QString>

namespace Discogs
{

class Track
{
public:
    Track(const QString &name = QString(), const QString &duration = QString());
    Track(const Track &other);

    ~Track();

    Track &operator=(const Track &other);

    bool operator==(const Track &other) const;

    QString title() const;

    QString duration() const;

private:
    class Private;
    Private *const d;
};

}

#endif // DISCOGS_TRACK_H
