#pragma once

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QEvent>

#include "statistics/data_frame_pool.hpp"

namespace ui
{
    class SmallTimeGraph : public QWidget {
        Q_OBJECT

    public:
        explicit SmallTimeGraph(statistics::DataFramePool& dataPool, int stackIndex, QWidget* parent = nullptr);

        void fillWithData();

    signals:
        void cardClicked(int index);

    private:
        int m_stackIndex;
        statistics::DataFramePool& m_dataPool;

        QChart* m_chart;
        QChartView* m_chartView;

        void fillChart(QBarSet* set, QStringList& categories);
        bool eventFilter(QObject* obj, QEvent* event) override;
    };
    
} // namespace ui
