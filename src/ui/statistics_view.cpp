#include "ui/statistics_view.hpp"

#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "statistics/data_frame_view.hpp"
#include "statistics/util.hpp"

namespace ui
{
    StatisticsView::StatisticsView(statistics::DataFramePool& dataPool, QWidget* parent) 
        : QWidget(parent), m_dataPool(dataPool) {

        m_stack = new QStackedWidget(this);

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(m_stack);
        layout->addStretch();
        setLayout(layout);

        QWidget* smallView = new QWidget(m_stack);
        createSmallView(smallView);

        
        m_bigSongsView = new RankingView(dataPool, this, "Songs");
        m_bigArtistsView = new RankingView(dataPool, this, "Artists");
        m_bigAlbumsView = new RankingView(dataPool, this, "Albums");
        
        m_stack->addWidget(smallView);
        m_stack->addWidget(m_bigSongsView);
        m_stack->addWidget(m_bigArtistsView);
        m_stack->addWidget(m_bigAlbumsView);
    }

    void StatisticsView::createSmallView(QWidget* smallView) {
        QVBoxLayout* smallViewLayout = new QVBoxLayout(smallView);

        QHBoxLayout* smallViewLayoutTop = new QHBoxLayout();
        smallViewLayoutTop->setContentsMargins(20, 20, 20, 20);
        smallViewLayoutTop->setSpacing(16);

        QHBoxLayout* smallViewLayoutBottom = new QHBoxLayout();
        smallViewLayoutBottom->setContentsMargins(20, 20, 20, 20);
        smallViewLayoutBottom->setSpacing(16);

        m_topSongsCard = new SmallViewCard("Top Songs", 1);
        m_topArtistsCard = new SmallViewCard("Top Artists", 2);
        m_topAlbumsCard = new SmallViewCard("Top Albums", 3);

        m_smallTimeGraph = new SmallTimeGraph(m_dataPool, 4);

        smallViewLayoutTop->addWidget(m_topSongsCard);
        smallViewLayoutTop->addWidget(m_topArtistsCard);

        smallViewLayoutBottom->addWidget(m_topAlbumsCard);
        smallViewLayoutBottom->addWidget(m_smallTimeGraph);

        smallViewLayout->addLayout(smallViewLayoutTop);
        smallViewLayout->addLayout(smallViewLayoutBottom);

        connect(m_topSongsCard, &SmallViewCard::cardClicked, this, &StatisticsView::switchView);
        connect(m_topArtistsCard, &SmallViewCard::cardClicked, this, &StatisticsView::switchView);
        connect(m_topAlbumsCard, &SmallViewCard::cardClicked, this, &StatisticsView::switchView);
        connect(m_smallTimeGraph, &SmallTimeGraph::cardClicked, this, &StatisticsView::switchView);
    }

    void StatisticsView::fillWithData() {
        statistics::DataFrameView& dfv = m_dataPool.getDataFrameViewForRange();

        m_topSongsCard->fillWithData(dfv.getSongsRanked(), [](const statistics::SongRankingEntry& entry) {return entry.title;});
        m_topArtistsCard->fillWithData(dfv.getArtistsRanked(), [](const statistics::ListeningTimeRankingEntry& entry) {return entry.name;});
        m_topAlbumsCard->fillWithData(dfv.getAlbumsRanked(), [](const statistics::ListeningTimeRankingEntry& entry) {return entry.name;});
        m_smallTimeGraph->fillWithData();

        m_bigSongsView->fillWithData();
        m_bigArtistsView->fillWithData();
        m_bigAlbumsView->fillWithData();
    }

    void StatisticsView::switchView(int index) {
        qDebug("%d clicked", index);
        m_stack->setCurrentIndex(index);
    }

    void StatisticsView::selectMainView() {
        m_stack->setCurrentIndex(0);
    }
    
} // namespace ui
