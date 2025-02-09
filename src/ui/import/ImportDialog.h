#pragma once

#include "data/concert/Concert.h"
#include "data/movie/Movie.h"
#include "data/tv_show/TvShow.h"
#include "data/tv_show/TvShowEpisode.h"
#include "import/FileWorker.h"
#include "network/DownloadManager.h"
#include "network/DownloadManagerElement.h"
#include "ui/renamer/RenamerDialog.h"

#include <QCloseEvent>
#include <QDialog>
#include <QPointer>
#include <QThread>
#include <QTimer>

namespace Ui {
class ImportDialog;
}

class ImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportDialog(QWidget* parent = nullptr);
    ~ImportDialog() override;
    void setFiles(QStringList files);
    QStringList files();
    void setExtraFiles(QStringList extraFiles);
    QStringList extraFiles();
    void setImportDir(QString dir);
    QString importDir();

public slots:
    int exec() override;
    int execMovie(QString searchString);
    int execTvShow(QString searchString, TvShow* tvShow);
    int execConcert(QString searchString);
    void reject() override;
    void accept() override;

private slots:
    void onMovieChosen();
    void onMovieLoadDone(Movie* movie);
    void onConcertChosen();
    void onConcertLoadDone(Concert* concert);
    void onTvShowChosen();
    void onEpisodeLoadDone(TvShowEpisode* episode);
    void onImport();
    void onFileWatcherTimeout();
    void onMovingFilesFinished();
    void onEpisodeDownloadFinished(DownloadManagerElement elem);

private:
    Ui::ImportDialog* ui = nullptr;
    QString m_type;
    QPointer<Movie> m_movie;
    QPointer<Concert> m_concert;
    QPointer<TvShow> m_show;
    QPointer<TvShowEpisode> m_episode;
    QStringList m_files;
    QStringList m_extraFiles;
    QString m_importDir;
    bool m_separateFolders = false;
    QTimer m_timer;
    QMap<QString, QString> m_filesToMove;
    QPointer<QThread> m_workerThread;
    QPointer<FileWorker> m_worker;
    QStringList m_newFiles;
    DownloadManager* m_posterDownloadManager = nullptr;

    void setDefaults(Renamer::RenameType renameType);
    void storeDefaults();
};
