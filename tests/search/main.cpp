#include <QTest>

#include "SearchResult.h"

#include <QFile>

class SearchTest: public QObject
{
    Q_OBJECT

private slots:
    void search();
};

void SearchTest::search()
{
    QFile file(":/json/search.json");
    file.open(QFile::ReadOnly);
    const QByteArray content = file.readAll();

    Discogs::SearchResult result;
    try {
        result.append(content);
        QCOMPARE(result.artists().size(), 2);
        QCOMPARE(result.labels().size(), 2);
        QCOMPARE(result.releases().size(), 46);
    }
    catch (const std::exception &e)
    {
        QFAIL(e.what());
    }
}

QTEST_MAIN(SearchTest)
#include "main.moc"
