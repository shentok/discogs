#include <QTest>

#include "Master.h"
#include "Track.h"

#include <QBuffer>
#include <QHash>
#include <QFile>
#include <QNetworkAccessManager>
#include <QAbstractNetworkCache>

class NetworkMemoryCache : public QAbstractNetworkCache
{
    Q_OBJECT
public:
    ~NetworkMemoryCache();

    qint64 cacheSize() const override;

    QIODevice *data(const QUrl &url) override;

    void insert(QIODevice *device) override;

    QNetworkCacheMetaData metaData(const QUrl &url) override;

    QIODevice *prepare(const QNetworkCacheMetaData &metaData) override;

    bool remove(const QUrl &url) override;

    void updateMetaData(const QNetworkCacheMetaData &metaData) override;

    void clear() override;

private:
    QHash<QUrl, QIODevice *> m_inserting;
    QHash<QUrl, QByteArray> m_cache;
};

NetworkMemoryCache::~NetworkMemoryCache()
{
    qDeleteAll(m_inserting);
    m_inserting.clear();
    m_cache.clear();
}

qint64 NetworkMemoryCache::cacheSize() const
{
    return 0;
}

QIODevice *NetworkMemoryCache::data(const QUrl &url)
{
    if (!m_cache.contains(url)) {
        return nullptr;
    }

    QBuffer *buffer = new QBuffer;
    buffer->setData(m_cache[url]);

    return buffer;
}

void NetworkMemoryCache::insert(QIODevice *device)
{
    QHashIterator<QUrl, QIODevice *> it(m_inserting);
    while (it.hasNext()) {
        it.next();

        if (it.value() == device) {
            const QUrl url = it.key();

            m_cache.insert(url, device->readAll());

            m_inserting.remove(url);
            delete device;
        }
    }
}

QNetworkCacheMetaData NetworkMemoryCache::metaData(const QUrl &url)
{
    if (!m_cache.contains(url)) {
        return QNetworkCacheMetaData();
    }

    QNetworkCacheMetaData metaData;
    metaData.setUrl(url);

    return metaData;
}

QIODevice *NetworkMemoryCache::prepare(const QNetworkCacheMetaData &metaData)
{
    if (!metaData.isValid() || !metaData.url().isValid() || !metaData.saveToDisk()) {
        return nullptr;
    }

    if (!m_inserting.contains(metaData.url())) {
        m_inserting[metaData.url()] = new QBuffer;
    }

    return m_inserting[metaData.url()];
}

bool NetworkMemoryCache::remove(const QUrl &url)
{
    delete m_inserting.value(url, 0);
    m_inserting.remove(url);

    return m_cache.remove(url) > 0;
}

void NetworkMemoryCache::updateMetaData(const QNetworkCacheMetaData &metaData)
{
    const QUrl url = metaData.url();

    QIODevice *const oldDevice = data(url);
    QIODevice *const newDevice = prepare(metaData);

    if (newDevice != nullptr && oldDevice != nullptr) {
        char buffer[1024];
        while (!oldDevice->atEnd()) {
            const qint64 read = oldDevice->read(buffer, sizeof(buffer));
            newDevice->write(buffer, read);
        }

        insert(newDevice);
    }

    if (oldDevice == nullptr) {
        qDebug() << "no data available for" << url;
    }

    if (newDevice == nullptr) {
        qDebug() << "preparation failed for" << url;
    }

    delete oldDevice;
}

void NetworkMemoryCache::clear()
{
    qDeleteAll(m_inserting);
    m_inserting.clear();
    m_cache.clear();
}

class MastersTest: public QObject
{
    Q_OBJECT
public:
    MastersTest();

private slots:
    void initTestCase();
    void masters();

private:
    QNetworkAccessManager m_networkAccess;
    NetworkMemoryCache m_networkCache;
};

MastersTest::MastersTest()
{
    m_networkAccess.setCache(&m_networkCache);
}

void MastersTest::initTestCase()
{
}

void MastersTest::masters()
{
    QFile file(":/json/17371.json");
    file.open(QFile::ReadOnly);
    const QByteArray content = file.readAll();

    Discogs::Master master;
    try {
        master.setJson(content);
        QCOMPARE(master.title(), QString("Let Us Replay!"));
        QCOMPARE(master.tracks().size(), 12);
        QCOMPARE(master.tracks()[0], Discogs::Track("Atomic Moog 2000 (Cornelius Mix)", ""));
    }
    catch (const std::exception &e)
    {
        QFAIL(e.what());
    }
}

QTEST_MAIN(MastersTest)
#include "main.moc"
