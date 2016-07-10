#include "Artist.h"

#include <reader.h>
#include <elements.h>

#include <QByteArray>

#include <istream>

namespace Discogs
{

class Artist::Private
{
public:
    Private(const QString &name = QString(), const QUrl &resourceUrl = QUrl());

    QString m_name;
    QUrl m_releasesUrl;
};

Artist::Private::Private(const QString &name, const QUrl &releasesUrl) :
    m_name(name),
    m_releasesUrl(releasesUrl)
{
}

Artist::Artist() :
    d(new Private)
{
}

Artist::~Artist()
{
    delete d;
}

void Artist::setJson(const QByteArray &jsonData)
{
    std::istringstream in(jsonData.constData());

    d->m_name.clear();
    d->m_releasesUrl.clear();

    json::Object object;
    json::Reader::Read(object, in);

    const json::String &name = object["name"];
    const json::String &releases_url = object["releases_url"];

    d->m_name = QString::fromStdString(name.Value());
    d->m_releasesUrl = QString::fromStdString(releases_url.Value());
}

Artist &Artist::operator=(const Artist &other)
{
    d->m_name = other.name();
    d->m_releasesUrl = other.releasesUrl();

    return *this;
}

QString Artist::name() const
{
    return d->m_name;
}

QUrl Artist::releasesUrl() const
{
    return  d->m_releasesUrl;
}

}
