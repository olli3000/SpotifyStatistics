#include "ui/big_view_base.hpp"

#include <QPushButton>

#include "ui/statistics_view.hpp"

namespace ui
{
    BigViewBase::BigViewBase(statistics::DataFramePool& dataPool, StatisticsView* parentView, QWidget* parent)
        : QWidget(parent), m_dataPool(dataPool) {
        
        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(20, 20, 20, 20);
        mainLayout->setSpacing(16);

        QHBoxLayout* topBarLayout = new QHBoxLayout();

        QPushButton* backButton = new QPushButton("Back", this);
        connect(backButton, &QPushButton::clicked, parentView, &StatisticsView::selectMainView);
        topBarLayout->addWidget(backButton);
        topBarLayout->addStretch();

        mainLayout->addLayout(topBarLayout);
    }

    BigViewBase::~BigViewBase() {}
    
} // namespace ui
