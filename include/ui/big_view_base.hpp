#pragma once

#include <QWidget>
#include <QHBoxLayout>

#include "statistics/data_frame_pool.hpp"
#include "statistics/util.hpp"

namespace ui
{
    class StatisticsView;
    class BigViewBase : public QWidget {
        Q_OBJECT

    public:
        explicit BigViewBase(statistics::DataFramePool& dataPool, StatisticsView* parentView, QWidget* parent = nullptr);
        virtual ~BigViewBase() = 0;

        virtual void fillWithData() = 0;
        virtual void fillWithData(statistics::TimeRange& timeRange) = 0;

    protected:
        statistics::DataFramePool& m_dataPool;

        StatisticsView* parentView;
        QHBoxLayout* m_childLayout;
    };
    
} // namespace ui
