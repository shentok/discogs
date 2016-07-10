#include "ArtistResult.h"

#include <QSharedData>

namespace Discogs
{

class ArtistResult::Private : public QSharedData
{
public:
    Private(const QString &name = QString(), const QUrl &thumbnailUrl = QUrl(), const QUrl &resourceUrl = QUrl());

    QString m_name;
    QUrl m_thumbnailUrl;
    QUrl m_resourceUrl;
};

ArtistResult::Private::Private(const QString &name, const QUrl &thumbnailUrl, const QUrl &resourceUrl) :
    m_name(name),
    m_thumbnailUrl(thumbnailUrl),
    m_resourceUrl(resourceUrl)
{
}

ArtistResult::ArtistResult() :
    d(new Private)
{
}

ArtistResult::ArtistResult(const ArtistResult &other) :
    d(new Private(other.name(), other.thumbnailUrl(), other.resourceUrl()))
{
}

ArtistResult::ArtistResult(const QString &name, const QUrl &thumbnailUrl, const QUrl &resourceUrl) :
    d(new Private(name, thumbnailUrl, resourceUrl))
{
}

ArtistResult::~ArtistResult()
{
    delete d;
}

ArtistResult &ArtistResult::operator=(const ArtistResult &other)
{
    d->m_name = other.name();
    d->m_thumbnailUrl = other.thumbnailUrl();
    d->m_resourceUrl = other.resourceUrl();

    return *this;
}

QString ArtistResult::name() const
{
    return d->m_name;
}

QUrl ArtistResult::thumbnailUrl() const
{
    return d->m_thumbnailUrl;
}

QUrl ArtistResult::resourceUrl() const
{
    return  d->m_resourceUrl;
}

}
