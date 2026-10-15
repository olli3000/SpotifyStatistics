#include "ui/statistics_view.hpp"

#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "ui/small_view_card.hpp"
#include "ui/small_time_graph.hpp"
#include "statistics/data_frame_view.hpp"
#include "statistics/util.hpp"

namespace ui
{
    StatisticsView::StatisticsView(statistics::DataFrame& data, QWidget* parent) 
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
        QVBoxLayout* smallViewLayout = new QVBoxLayout(smallView);

        QHBoxLayout* smallViewLayoutTop = new QHBoxLayout();
        smallViewLayoutTop->setContentsMargins(20, 20, 20, 20);
        smallViewLayoutTop->setSpacing(16);

        QHBoxLayout* smallViewLayoutBottom = new QHBoxLayout();
        smallViewLayoutBottom->setContentsMargins(20, 20, 20, 20);
        smallViewLayoutBottom->setSpacing(16);

        SmallViewCard* topSongsCard = new SmallViewCard("Top Songs", 1);
        SmallViewCard* topArtistsCard = new SmallViewCard("Top Artists", 2);
        SmallViewCard* topAlbumsCard = new SmallViewCard("Top Albums", 3);

        SmallTimeGraph* smallTimeGraph = new SmallTimeGraph(m_data, 4);

        statistics::DataFrameView dfv{m_data};
        topSongsCard->fillData(dfv.getSongsRanked(), [](const statistics::SongRankingEntry& entry) {return entry.title;});
        topArtistsCard->fillData(dfv.getArtistsRanked(), [](const statistics::ListeningTimeRankingEntry& entry) {return entry.name;});
        topAlbumsCard->fillData(dfv.getAlbumsRanked(), [](const statistics::ListeningTimeRankingEntry& entry) {return entry.name;});

        smallViewLayoutTop->addWidget(topSongsCard);
        smallViewLayoutTop->addWidget(topArtistsCard);

        smallViewLayoutBottom->addWidget(topAlbumsCard);
        smallViewLayoutBottom->addWidget(smallTimeGraph);

        smallViewLayout->addLayout(smallViewLayoutTop);
        smallViewLayout->addLayout(smallViewLayoutBottom);

        connect(topSongsCard, &SmallViewCard::cardClicked, this, &StatisticsView::switchView);
        connect(topArtistsCard, &SmallViewCard::cardClicked, this, &StatisticsView::switchView);
        connect(topAlbumsCard, &SmallViewCard::cardClicked, this, &StatisticsView::switchView);
        connect(smallTimeGraph, &SmallTimeGraph::cardClicked, this, &StatisticsView::switchView);
    }

    void StatisticsView::switchView(int index) {
        qDebug("%d clicked", index);
        m_stack->setCurrentIndex(index);
    }
    
} // namespace ui
