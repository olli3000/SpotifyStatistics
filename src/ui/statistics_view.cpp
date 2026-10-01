#include "ui/statistics_view.hpp"

#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "ui/small_view_card.hpp"
#include "statistics/util.hpp"

namespace ui
{
    StatisticsView::StatisticsView(statistics::DataFrameView& data, QWidget* parent) 
        : QWidget(parent), m_data(data) {

        m_stack = new QStackedWidget(this);

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(m_stack);
        layout->addStretch();
        setLayout(layout);

        QWidget* smallView = new QWidget(m_stack);
        createSmallView(smallView);

        m_stack->addWidget(smallView);
        m_stack->addWidget(new QLabel("SongsCard"));
        m_stack->addWidget(new QLabel("ArtistsCard"));
    }

    void StatisticsView::createSmallView(QWidget* smallView) {
        QHBoxLayout* smallViewLayout = new QHBoxLayout(smallView);
        smallViewLayout->setContentsMargins(20, 20, 20, 20);
        smallViewLayout->setSpacing(16);

        SmallViewCard* topSongsCard = new SmallViewCard(m_data, "Top Songs", 1);
        SmallViewCard* topArtistsCard = new SmallViewCard(m_data, "Top Artists", 2);

        topSongsCard->fillData(m_data.getSongsRanked(), [](const statistics::SongRankingEntry& entry) {return entry.title;});
        topArtistsCard->fillData(m_data.getArtistsRanked(), [](const statistics::ArtistRankingEntry& entry) {return entry.name;});

        smallViewLayout->addWidget(topSongsCard);
        smallViewLayout->addWidget(topArtistsCard);

        connect(topSongsCard, &SmallViewCard::cardClicked, this, &StatisticsView::switchView);
        connect(topArtistsCard, &SmallViewCard::cardClicked, this, &StatisticsView::switchView);
    }

    void StatisticsView::switchView(int index) {
        qDebug("%d clicked", index);
        m_stack->setCurrentIndex(index);
    }
    
} // namespace ui
