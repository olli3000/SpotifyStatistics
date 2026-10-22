#include "ui/total_stats_overview.hpp"

#include <string>

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>

namespace ui {

    TotalStatsOverview::TotalStatsOverview(statistics::DataFramePool& dataPool, QWidget* parent) : QWidget(parent), m_dataPool(dataPool) {

        QHBoxLayout* mainLayout = new QHBoxLayout(this);
        mainLayout->setContentsMargins(20, 20, 20, 20);
        mainLayout->setSpacing(16);

        m_songsCard = createCard();
        m_artistsCard = createCard();
        m_timeCard = createCard();


        mainLayout->addWidget(m_songsCard);
        mainLayout->addStretch(1);
        mainLayout->addWidget(m_artistsCard);
        mainLayout->addStretch(1);
        mainLayout->addWidget(m_timeCard);
    }

    QWidget* TotalStatsOverview::createCard() {
        QWidget* card = new QWidget(this);

        QVBoxLayout* layout = new QVBoxLayout(card);
        layout->setContentsMargins(20, 20, 20, 20);
        layout->setSpacing(16);

        return card;
    }

    void TotalStatsOverview::fillWithData() {
        statistics::DataFrameView& data = m_dataPool.getDataFrameViewForRange();

        fillCard(m_songsCard, "Songs", std::to_string(data.getNumberOfSongs()));
        fillCard(m_artistsCard, "Artists", std::to_string(data.getNumberOfArtists()));
        fillCard(m_timeCard, "Hours", std::to_string(data.getTotalStreamingTime() / 3'600'000.0));
    }

    void TotalStatsOverview::fillCard(QWidget* card, const std::string& name, const std::string& data) {
        card->layout()->addWidget(new QLabel(name.data()));
        card->layout()->addWidget(new QLabel(data.data()));
    }

    void TotalStatsOverview::mousePressEvent(QMouseEvent* event) {
        if (event->button() == Qt::LeftButton) {
            emit clicked();
        }

        QWidget::mousePressEvent(event);
    }

}