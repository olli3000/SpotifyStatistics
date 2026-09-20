#include "ui/main_window.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "ui/total_stats_overview.hpp"
#include "ui/statistics_view.hpp"
#include "statistics/data_frame_view.hpp"

namespace ui
{
    MainWindow::MainWindow(statistics::DataFrame& data, QWidget* parent) : QMainWindow(parent) {
        setWindowTitle("Spotify Statistics");
        setMinimumSize(1280, 720);

        m_centralWidget = new QWidget(this);
        setCentralWidget(m_centralWidget);

        auto* mainLayout = new QVBoxLayout(m_centralWidget);
        mainLayout->setContentsMargins(20, 20, 20, 20);
        mainLayout->setSpacing(16);

        m_title = new QLabel("Spotify Statistics");

        // statistics::DataFrameView view{data, 
        //     statistics::TimeRange{std::chrono::sys_days{std::chrono::year_month_day{floor<std::chrono::days>(std::chrono::system_clock::now())} - std::chrono::months{12}}, 
        //     std::chrono::system_clock::now()}
        // };
        statistics::DataFrameView view{data, data.getFullTimeRange()};
        
        TotalStatsOverview* statsCard = new TotalStatsOverview(view, this);
        StatisticsView* statisticsView = new StatisticsView(view, this);
        
        mainLayout->addWidget(m_title);
        mainLayout->addWidget(statsCard);
        mainLayout->addWidget(statisticsView);
        mainLayout->addStretch();
    }

} // namespace ui
