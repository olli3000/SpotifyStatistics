#pragma once

#include <QWidget>
#include <QChart>
#include <QBarSet>
#include <QBarCategoryAxis>

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

    protected:
        void mousePressEvent(QMouseEvent* event) override;

    private:
        int m_stackIndex;
        statistics::DataFramePool& m_dataPool;

        QChart* m_chart;

        void fillChart(QBarSet* set, QStringList& categories);
    };
    
} // namespace ui
