#pragma once

#include "model/music/MusicModelRoles.h"

#include <QPainter>
#include <QTreeView>
#include <QWidget>

class MusicTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit MusicTreeView(QWidget* parent = nullptr);
    ~MusicTreeView() override = default;

protected:
    void drawBranches(QPainter* painter, const QRect& rect, const QModelIndex& index) const override;
    void drawRow(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

private:
    const int m_albumIndent{40};
    const int m_branchIndent{30};

    void drawArtistRow(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void drawAlbumRow(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    int drawNewIcon(QPainter* painter,
        const QStyleOptionViewItem& option,
        const QModelIndex& index,
        int branchIndent) const;
    void setAlternateRowColors(QStyleOptionViewItem& option, const QModelIndex& index) const;

    inline bool isAlbumRow(const QModelIndex& index) const
    {
        using namespace mediaelch;
        return MusicType(index.data(MusicRoles::Type).toInt()) == MusicType::Album;
    }
    inline bool isArtistRow(const QModelIndex& index) const
    {
        using namespace mediaelch;
        return MusicType(index.data(MusicRoles::Type).toInt()) == MusicType::Artist;
    }
};
