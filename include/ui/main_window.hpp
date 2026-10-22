#pragma once

#include <QMainWindow>

#include "ui/total_stats_overview.hpp"
#include "ui/statistics_view.hpp"
#include "statistics/data_frame_pool.hpp"

class QWidget;
class QLabel;

namespace ui 
{
    class MainWindow : public QMainWindow {
        Q_OBJECT
        
    public:
        explicit MainWindow(statistics::DataFramePool& dataPool, QWidget *parent = nullptr);

        void fillWithData();

    private:
        QWidget* m_centralWidget;
        QLabel* m_title;

        TotalStatsOverview* m_statsCard;
        StatisticsView* m_statisticsView;
    };

} // namespace ui
