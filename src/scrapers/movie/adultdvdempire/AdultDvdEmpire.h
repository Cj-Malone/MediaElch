#pragma once

#include "network/NetworkManager.h"
#include "scrapers/movie/MovieScraper.h"
#include "scrapers/movie/adultdvdempire/AdultDvdEmpireApi.h"
#include "scrapers/movie/adultdvdempire/AdultDvdEmpireScrapeJob.h"

#include <QObject>
#include <QWidget>

namespace mediaelch {
namespace scraper {

class AdultDvdEmpire : public MovieScraper
{
    Q_OBJECT
public:
    explicit AdultDvdEmpire(QObject* parent = nullptr);
    static constexpr const char* ID = "adult-dvd-empire";

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
    mediaelch::network::NetworkManager m_network;

private:
    AdultDvdEmpireApi m_api;
    AdultDvdEmpireScrapeJob m_scrapeJob;
    mediaelch::network::NetworkManager* network();
    void parseAndAssignInfos(QString html, Movie* movie, QSet<MovieScraperInfo> infos);
    QString replaceEntities(QString str) const;
};

} // namespace scraper
} // namespace mediaelch
