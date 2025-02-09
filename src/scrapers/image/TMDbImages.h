#pragma once

#include "data/movie/Movie.h"
#include "scrapers/image/ImageProvider.h"
#include "scrapers/movie/tmdb/TmdbMovie.h"

namespace mediaelch {
namespace scraper {

class TMDbImages : public ImageProvider
{
    Q_OBJECT
public:
    static QString ID;

public:
    explicit TMDbImages(QObject* parent = nullptr);
    ~TMDbImages() override = default;

    const ScraperMeta& meta() const override;

    void movieImages(Movie* movie, TmdbId tmdbId, QSet<ImageType> types) override;
    void moviePosters(TmdbId tmdbId) override;
    void movieBackdrops(TmdbId tmdbId) override;
    void movieLogos(TmdbId tmdbId) override;
    void movieBanners(TmdbId tmdbId) override;
    void movieThumbs(TmdbId tmdbId) override;
    void movieClearArts(TmdbId tmdbId) override;
    void movieCdArts(TmdbId tmdbId) override;

    void concertImages(Concert* concert, TmdbId tmdbId, QSet<ImageType> types) override;
    void concertPosters(TmdbId tmdbId) override;
    void concertBackdrops(TmdbId tmdbId) override;
    void concertLogos(TmdbId tmdbId) override;
    void concertClearArts(TmdbId tmdbId) override;
    void concertCdArts(TmdbId tmdbId) override;

    void tvShowImages(TvShow* show, TvDbId tvdbId, QSet<ImageType> types, const mediaelch::Locale& locale) override;
    void tvShowPosters(TvDbId tvdbId, const mediaelch::Locale& locale) override;
    void tvShowBackdrops(TvDbId tvdbId, const mediaelch::Locale& locale) override;
    void tvShowLogos(TvDbId tvdbId, const mediaelch::Locale& locale) override;
    void tvShowClearArts(TvDbId tvdbId, const mediaelch::Locale& locale) override;
    void tvShowCharacterArts(TvDbId tvdbId, const mediaelch::Locale& locale) override;
    void tvShowBanners(TvDbId tvdbId, const mediaelch::Locale& locale) override;
    void tvShowEpisodeThumb(TvDbId tvdbId,
        SeasonNumber season,
        EpisodeNumber episode,
        const mediaelch::Locale& locale) override;
    void tvShowSeason(TvDbId tvdbId, SeasonNumber season, const mediaelch::Locale& locale) override;
    void tvShowSeasonBanners(TvDbId tvdbId, SeasonNumber season, const mediaelch::Locale& locale) override;
    void tvShowSeasonBackdrops(TvDbId tvdbId, SeasonNumber season, const mediaelch::Locale& locale) override;
    void tvShowThumbs(TvDbId tvdbId, const mediaelch::Locale& locale) override;
    void tvShowSeasonThumbs(TvDbId tvdbId, SeasonNumber season, const mediaelch::Locale& locale) override;

    void artistFanarts(MusicBrainzId mbId) override;
    void artistLogos(MusicBrainzId mbId) override;
    void artistThumbs(MusicBrainzId mbId) override;
    void albumCdArts(MusicBrainzId mbId) override;
    void albumThumbs(MusicBrainzId mbId) override;
    void artistImages(Artist* artist, MusicBrainzId mbId, QSet<ImageType> types) override;
    void albumImages(Album* album, MusicBrainzId mbId, QSet<ImageType> types) override;
    void albumBooklets(MusicBrainzId mbId) override;

    bool hasSettings() const override;
    void loadSettings(ScraperSettings& settings) override;
    void saveSettings(ScraperSettings& settings) override;
    QWidget* settingsWidget() override;

public slots:
    void searchMovie(QString searchStr, int limit = 0) override;
    void searchConcert(QString searchStr, int limit = 0) override;
    void searchTvShow(QString searchStr, mediaelch::Locale locale, int limit = 0) override;
    void searchArtist(QString searchStr, int limit = 0) override;
    void searchAlbum(QString artistName, QString searchStr, int limit = 0) override;

private slots:
    void onSearchMovieFinished(mediaelch::scraper::MovieSearchJob* searchJob);
    void onLoadImagesFinished();

private:
    ScraperMeta m_meta;

    int m_searchResultLimit = 0;
    mediaelch::scraper::TmdbMovie* m_tmdb = nullptr;
    Movie* m_dummyMovie = nullptr;
    ImageType m_imageType = ImageType::None;
};

} // namespace scraper
} // namespace mediaelch
