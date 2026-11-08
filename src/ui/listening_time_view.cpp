#include "ui/listening_time_view.hpp"

#include <QLabel>

namespace ui
{
    ListeningTimeView::ListeningTimeView(statistics::DataFramePool& dataPool, StatisticsView* parentView, QWidget* parent) : BigViewBase(dataPool, parentView, parent) {
        layout()->addWidget(new QLabel("Listening Time"));
    }

    void ListeningTimeView::fillWithData() {
        qDebug() << "Filled Listening Time";
    }

    void ListeningTimeView::fillWithData(statistics::TimeRange& timeRange) {
        
    }
    
} // namespace ui
