#include "SearchResult.h"

#include <QByteArray>
#include <QDebug>

#include <reader.h>
#include <elements.h>

#include <istream>

namespace Discogs
{

class SearchResult::Private
{
public:
    Private();

    QVector<ArtistResult> m_artists;
    QVector<Label> m_labels;
    QVector<Release> m_releases;
};

SearchResult::Private::Private()
{
}

SearchResult::SearchResult() :
    d(new Private)
{
}

SearchResult::~SearchResult()
{
    delete d;
}

void SearchResult::append(const QByteArray &jsonData)
{
    std::istringstream in(jsonData.constData());

    json::Object object;
    json::Reader::Read(object, in);
    const json::Array &results = object["results"];

    for (size_t i = 0; i < results.Size(); ++i) {
        const json::Object &entry = results[i];
        const json::String &type = entry["type"];
        if (type.Value() == "artist") {
            const json::String &thumb = entry["thumb"];
            const json::String &title = entry["title"];
//            "uri": "/artist/946-Coldcut",
            const json::String &resource_url = entry["resource_url"];

            const QString name = QString::fromStdString(title.Value());
            const QUrl thumbnailUrl(QString::fromStdString(thumb.Value()));
            const QUrl resourceUrl(QString::fromStdString(resource_url.Value()));
            d->m_artists.append(ArtistResult(name, thumbnailUrl, resourceUrl));
        }
        else if (type.Value() == "release" || type.Value() == "master") {
            const json::Array &style = entry["style"]; // : ["Tech House", "Minimal"],
            const json::String &thumb = entry["thumb"];
            const json::Array &format = entry["format"]; // : ["Vinyl", "12\"", "Single"],
            const json::String &coutry = entry["country"];
            const json::Array &barcode = entry["barcode"]; // : ["8 80319 14841 5", "LC 00494"],
            const json::String &uri = entry["uri"];
            const json::Number &communityHave = entry["community"]["have"];
            const json::Number &communityWant = entry["community"]["want"];
            const json::Array &label = entry["label"];
            const json::String &catno = entry["catno"];
            const json::String &year = entry["year"];
            const json::Array &genre = entry["genre"]; // : ["Electronic"],
            const json::String &title = entry["title"];
            const json::String &resource_url = entry["resource_url"];

            d->m_releases.append(Release());
        }
        else if (type.Value() == "label") {
            d->m_labels.append(Label());
        }
        else {
            qDebug() << "unknown type" << QString::fromStdString(type.Value());
        }
    }
}

QVector<ArtistResult> SearchResult::artists() const
{
    return d->m_artists;
}

QVector<Label> SearchResult::labels() const
{
    return d->m_labels;
}

QVector<Release> SearchResult::releases() const
{
    return d->m_releases;
}

}
