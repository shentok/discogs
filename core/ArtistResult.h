#ifndef DISCOGS_ARTISTRESULT_H
#define DISCOGS_ARTISTRESULT_H

#include <QString>
#include <QUrl>

namespace Discogs
{

class ArtistResult
{
public:
    ArtistResult();
    ArtistResult(const ArtistResult &other);
    ArtistResult(const QString &name, const QUrl &thumbnailUrl, const QUrl &resourceUrl);

    ~ArtistResult();

    ArtistResult &operator=(const ArtistResult &other);

    QString name() const;

    QUrl thumbnailUrl() const;

    QUrl resourceUrl() const;

private:
    class Private;
    Private *const d;
};

}

#endif // DISCOGS_ARTISTRESULT_H
