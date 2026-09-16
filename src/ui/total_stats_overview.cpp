#include "ui/total_stats_overview.hpp"

#include <string>

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>

namespace ui {

    TotalStatsOverview::TotalStatsOverview(statistics::DataFrame& data, QWidget* parent) : QWidget(parent) {

        QHBoxLayout* mainLayout = new QHBoxLayout(this);
        mainLayout->setContentsMargins(20, 20, 20, 20);
        mainLayout->setSpacing(16);

        QWidget* songsCard = createCard("Songs", std::to_string(data.getNumberOfSongs()));
        QWidget* artistsCard = createCard("Artists", std::to_string(data.getNumberOfArtists()));
        QWidget* timeCard = createCard("Hours", std::to_string(data.getTotalStreamingTime() / 3'600'000.0));


        mainLayout->addWidget(songsCard);
        mainLayout->addStretch(1);
        mainLayout->addWidget(artistsCard);
        mainLayout->addStretch(1);
        mainLayout->addWidget(timeCard);
    }

    QWidget* TotalStatsOverview::createCard(const std::string& name, const std::string& data) {
        QWidget* card = new QWidget(this);

        QVBoxLayout* layout = new QVBoxLayout(card);
        layout->setContentsMargins(20, 20, 20, 20);
        layout->setSpacing(16);

        layout->addWidget(new QLabel(name.data()));
        layout->addWidget(new QLabel(data.data()));

        return card;
    }

    void TotalStatsOverview::mousePressEvent(QMouseEvent* event) {
        if (event->button() == Qt::LeftButton) {
            emit clicked();
        }

        QWidget::mousePressEvent(event);
    }

}