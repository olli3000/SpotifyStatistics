#include "ui/small_view_card.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>

namespace ui
{
    SmallViewCard::SmallViewCard(const QString& title, int stackIndex, QWidget* parent) 
        : QWidget(parent), m_stackIndex(stackIndex) {

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(20, 20, 20, 20);
        mainLayout->setSpacing(16);

        QLabel* titleLabel = new QLabel(title, this);

        m_contentLayout = new QVBoxLayout();

        mainLayout->addWidget(titleLabel);
        mainLayout->addLayout(m_contentLayout);
    }

    QWidget* SmallViewCard::createEntry(int place, const std::string_view& name, long listeningTime) {
        QWidget* card = new QWidget();

        QHBoxLayout* layout = new QHBoxLayout(card);

        layout->addWidget(new QLabel(std::to_string(place).data(), card));
        layout->addWidget(new QLabel(name.data(), card));
        layout->addStretch();
        layout->addWidget(new QLabel(QString("%1 %2").arg(std::to_string(listeningTime / 3'600'600).data()).arg("h"), card));

        return card;
    }

    void SmallViewCard::mousePressEvent(QMouseEvent* event) {
        if (event->button() == Qt::LeftButton) {
            emit cardClicked(m_stackIndex);
        }

        QWidget::mousePressEvent(event);
    }
    
} // namespace ui
