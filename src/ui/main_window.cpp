#include "ui/main_window.hpp"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "ui/total_stats_overview.hpp"
#include "ui/statistics_view.hpp"
#include "statistics/data_frame_view.hpp"

namespace ui
{
    MainWindow::MainWindow(statistics::DataFramePool& dataPool, QWidget* parent) : QMainWindow(parent) {
        setWindowTitle("Spotify Statistics");
        setMinimumSize(1280, 720);

        m_centralWidget = new QWidget(this);
        setCentralWidget(m_centralWidget);

        auto* mainLayout = new QVBoxLayout(m_centralWidget);
        mainLayout->setContentsMargins(20, 20, 20, 20);
        mainLayout->setSpacing(16);

        m_title = new QLabel("Spotify Statistics");
        
        m_statsCard = new TotalStatsOverview(dataPool, this);
        m_statisticsView = new StatisticsView(dataPool, this);
        
        mainLayout->addWidget(m_title);
        mainLayout->addWidget(m_statsCard);
        mainLayout->addWidget(m_statisticsView);
        mainLayout->addStretch();
    }

    void MainWindow::fillWithData() {
        m_statsCard->fillWithData();
        m_statisticsView->fillWithData();
    }

} // namespace ui
