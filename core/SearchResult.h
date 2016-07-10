#ifndef DISCOGS_SEARCHRESULT_H
#define DISCOGS_SEARCHRESULT_H

#include "ArtistResult.h"
#include "Label.h"
#include "Release.h"

#include <QVector>

class QByteArray;

namespace Discogs
{

class SearchResult
{
public:
    SearchResult();
    ~SearchResult();

    void append(const QByteArray &json);

    QVector<ArtistResult> artists() const;
    QVector<Label> labels() const;
    QVector<Release> releases() const;

private:
    class Private;
    Private *const d;
};

}

#endif // DISCOGS_SEARCHRESULT_H
