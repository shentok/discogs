#ifndef DISCOGS_MASTER_H
#define DISCOGS_MASTER_H

#include "Track.h"

#include <QString>
#include <QVector>

namespace Discogs
{

class Master
{
public:
    Master();

    ~Master();

    void setJson(const QByteArray &jsonData);

    Master &operator=(const Master &other);

    QString title() const;

    QVector<Track> tracks() const;

private:
    class Private;
    Private *const d;
};

}

#endif // DISCOGS_MASTER_H
