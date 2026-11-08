#pragma once

#include <QWidget>

#include "ui/big_view_base.hpp"
#include "statistics/util.hpp"

namespace ui
{
    class StatisticsView;
    class ListeningTimeView : public BigViewBase {
        Q_OBJECT
    
        public: 
            explicit ListeningTimeView(statistics::DataFramePool& dataPool, StatisticsView* parentView, QWidget* parent = nullptr);

            void fillWithData() override;
            void fillWithData(statistics::TimeRange& timeRange) override;
    };
    
} // namespace ui
