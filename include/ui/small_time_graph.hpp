#pragma once

#include <QWidget>
#include <QBarSet>

#include "statistics/data_frame.hpp"

namespace ui
{
    class SmallTimeGraph : public QWidget {
        Q_OBJECT

    public:
        explicit SmallTimeGraph(const statistics::DataFrame& data, int stackIndex, QWidget* parent = nullptr);

    signals:
        void cardClicked(int index);

    protected:
        void mousePressEvent(QMouseEvent* event) override;

    private:
        int m_stackIndex;
        const statistics::DataFrame& m_data;

        void fillChart(QBarSet* set, QStringList& categories);
    };
    
} // namespace ui
