#pragma once

#include <QWidget>

#include "statistics/data_frame.hpp"

class QStackedWidget;
namespace ui
{
    class StatisticsView : public QWidget {
        Q_OBJECT

    public:
        explicit StatisticsView(statistics::DataFrame& data, QWidget* parent = nullptr);

    public slots:
        void switchView(int index);

    private:
        void createSmallView(QWidget* smallView);

        statistics::DataFrame& m_data;
        QStackedWidget* m_stack;
    };

} // namespace ui
