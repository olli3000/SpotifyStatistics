#include "ui/top_artists_card.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QMouseEvent>

namespace ui
{
    TopArtistsCard::TopArtistsCard(statistics::DataFrame& data, int stackIndex, QWidget* parent) 
        : QWidget(parent), m_stackIndex(stackIndex) {

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(20, 20, 20, 20);
        mainLayout->setSpacing(16);

        QLabel* title = new QLabel("Top Artists", this);

        // QScrollArea* scrollArea = new QScrollArea(this);
        // scrollArea->setMinimumSize(800, 600);

        // QWidget* scrollAreaWidget = new QWidget(scrollArea);
        // scrollArea->setWidget(scrollAreaWidget);
        // scrollArea->setWidgetResizable(true);

        // QVBoxLayout* contentLayout = new QVBoxLayout(scrollAreaWidget);
        QVBoxLayout* contentLayout = new QVBoxLayout();

        int i = 0;
        for (auto& entry : data.getArtistsRanked()) {
            if (i == 5) break;

            i++;
            contentLayout->addWidget(createEntry(i, entry.name, entry.listeningTime));
        }

        mainLayout->addWidget(title);
        mainLayout->addLayout(contentLayout);
    }

    QWidget* TopArtistsCard::createEntry(int place, const std::string_view& name, long listeningTime) {
        QWidget* card = new QWidget();

        QHBoxLayout* layout = new QHBoxLayout(card);
        layout->setContentsMargins(20, 20, 20, 20);
        layout->setSpacing(16);

        layout->addWidget(new QLabel(std::to_string(place).data(), card));
        layout->addWidget(new QLabel(name.data(), card));
        layout->addStretch();
        layout->addWidget(new QLabel(QString("%1 %2").arg(std::to_string(listeningTime / 3'600'600).data()).arg("h"), card));

        return card;
    }

    void TopArtistsCard::mousePressEvent(QMouseEvent* event) {
        if (event->button() == Qt::LeftButton) {
            emit cardClicked(m_stackIndex);
        }

        QWidget::mousePressEvent(event);
    }
    
} // namespace ui
