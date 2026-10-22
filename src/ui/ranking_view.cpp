#include "ui/ranking_view.hpp"

#include <QLabel>

#include "ui/statistics_view.hpp"

namespace ui
{
    RankingView::RankingView(statistics::DataFramePool& dataPool, StatisticsView* parentView, std::string&& name, QWidget* parent) : BigViewBase(dataPool, parentView, parent), m_name(std::move(name)) {
        layout()->addWidget(new QLabel(m_name.data()));
    }

    void RankingView::fillWithData() {
        qDebug() << "Filled " << m_name.data();
    }
    
} // namespace ui
