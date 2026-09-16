#include "ui/statistics_view.hpp"

#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "ui/top_songs_card.hpp"
#include "ui/top_artists_card.hpp"

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
        QHBoxLayout* smallViewLayout = new QHBoxLayout(smallView);
        smallViewLayout->setContentsMargins(20, 20, 20, 20);
        smallViewLayout->setSpacing(16);

        TopSongsCard* topSongsCard = new TopSongsCard(m_data, 1);
        TopArtistsCard* topArtistsCard = new TopArtistsCard(m_data, 2);

        smallViewLayout->addWidget(topSongsCard);
        smallViewLayout->addWidget(topArtistsCard);

        connect(topSongsCard, &TopSongsCard::cardClicked, this, &StatisticsView::switchView);
        connect(topArtistsCard, &TopArtistsCard::cardClicked, this, &StatisticsView::switchView);
    }

    void StatisticsView::switchView(int index) {
        qDebug("%d clicked", index);
        m_stack->setCurrentIndex(index);
    }
    
} // namespace ui
