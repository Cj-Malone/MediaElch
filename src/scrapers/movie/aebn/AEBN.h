#pragma once

#include "AebnScrapeJob.h"
#include "network/NetworkManager.h"
#include "scrapers/movie/MovieScraper.h"
#include "scrapers/movie/aebn/AebnApi.h"

#include <QComboBox>
#include <QMap>
#include <QObject>
#include <QPointer>
#include <QWidget>

namespace mediaelch {
namespace scraper {

class AEBN : public MovieScraper
{
    Q_OBJECT
public:
    explicit AEBN(QObject* parent = nullptr);
    ~AEBN() override;
    static constexpr const char* ID = "aebn";

    const ScraperMeta& meta() const override;

    void initialize() override;
    bool isInitialized() const override;

    ELCH_NODISCARD MovieSearchJob* search(MovieSearchJob::Config config) override;

public:
    void loadData(QHash<MovieScraper*, mediaelch::scraper::MovieIdentifier> ids,
        Movie* movie,
        QSet<MovieScraperInfo> infos) override;
    bool hasSettings() const override;
    void loadSettings(ScraperSettings& settings) override;
    void saveSettings(ScraperSettings& settings) override;

    QSet<MovieScraperInfo> scraperNativelySupports() override;

    void changeLanguage(mediaelch::Locale locale) override;
    QWidget* settingsWidget() override;

private:
    ScraperMeta m_meta;
    AebnApi m_api;
    AebnScrapeJob m_scrapeJob;

    mediaelch::network::NetworkManager m_network;
    mediaelch::Locale m_language;
    QString m_genreId;
    QPointer<QWidget> m_widget;
    QComboBox* m_box;
    QComboBox* m_genreBox;

    void parseAndAssignInfos(QString html, Movie* movie, QSet<MovieScraperInfo> infos, QStringList& actorIds);
    void downloadActors(Movie* movie, QStringList actorIds);
    void parseAndAssignActor(QString html, Movie* movie, QString id);
};

} // namespace scraper
} // namespace mediaelch
