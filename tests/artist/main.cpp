#include <QTest>

#include "Artist.h"

#include <QFile>

class ArtistTest: public QObject
{
    Q_OBJECT

private slots:
    void search();
};

void ArtistTest::search()
{
    QFile file(":/json/artist.json");
    file.open(QFile::ReadOnly);
    const QByteArray content = file.readAll();

    Discogs::Artist artist;
    try {
        artist.setJson(content);
        QCOMPARE(artist.name(), QString("Coldcut"));
        QCOMPARE(artist.releasesUrl(), QUrl("https://api.discogs.com/artists/946/releases"));
    }
    catch (const std::exception &e)
    {
        QFAIL(e.what());
    }
}

QTEST_MAIN(ArtistTest)
#include "main.moc"
