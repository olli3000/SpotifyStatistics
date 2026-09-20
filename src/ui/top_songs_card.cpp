#include "ui/top_songs_card.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QMouseEvent>

namespace ui
{
    TopSongsCard::TopSongsCard(statistics::DataFrameView& data, int stackIndex, QWidget* parent) 
        : QWidget(parent), m_stackIndex(stackIndex) {

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(20, 20, 20, 20);
        mainLayout->setSpacing(16);

        QLabel* title = new QLabel("Top Artists", this);

        QVBoxLayout* contentLayout = new QVBoxLayout();

        int i = 0;
        for (auto& entry : data.getSongsRanked()) {
            if (i == 5) break;

            i++;
            contentLayout->addWidget(createEntry(i, entry.title, entry.listeningTime));
        }

        mainLayout->addWidget(title);
        mainLayout->addLayout(contentLayout);
    }

    QWidget* TopSongsCard::createEntry(int place, const std::string_view& name, long listeningTime) {
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

    void TopSongsCard::mousePressEvent(QMouseEvent* event) {
        if (event->button() == Qt::LeftButton) {
            emit cardClicked(m_stackIndex);
        }

        QWidget::mousePressEvent(event);
    }
    
} // namespace ui
