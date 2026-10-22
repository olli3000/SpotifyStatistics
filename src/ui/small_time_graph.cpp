#include "ui/small_time_graph.hpp"

#include <array>

#include <QVBoxLayout>
#include <QLabel>
#include <QBarSeries>
#include <QChartView>
#include <QMouseEvent>

#include "statistics/data_frame_view.hpp"

namespace ui
{
    constexpr std::array<std::string_view, 12> monthNames{
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    SmallTimeGraph::SmallTimeGraph(statistics::DataFramePool& dataPool, int stackIndex, QWidget* parent) : QWidget(parent), m_stackIndex(stackIndex), m_dataPool(dataPool) {

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        // mainLayout->setContentsMargins(20, 20, 20, 20);
        // mainLayout->setSpacing(16);

        m_chart = new QChart();
        m_chart->setTitle("Listening Time");

        QChartView* chartView = new QChartView(m_chart);

        // mainLayout->addWidget(titleLabel);
        mainLayout->addWidget(chartView);
    }

    void SmallTimeGraph::fillWithData() {
        QBarSet* set = new QBarSet("Month");
        QStringList categories{};

        fillChart(set, categories);

        QBarSeries* series = new QBarSeries();
        series->append(set);

        m_chart->addSeries(series);
        m_chart->legend()->setVisible(false);

        QBarCategoryAxis* axis = new QBarCategoryAxis();
        axis->append(categories);
        m_chart->addAxis(axis, Qt::AlignBottom);

        series->attachAxis(axis);
    }

    void SmallTimeGraph::fillChart(QBarSet* set, QStringList& categories) {
        namespace ch = std::chrono;

        auto timeRange = m_dataPool.getFullTimeRange();
        ch::year_month_day startDate{ch::floor<ch::days>(timeRange.begin)};
        ch::year_month_day endDate{ch::floor<ch::days>(timeRange.end)};

        ch::year currentYear = startDate.year();
        ch::year finalYear = endDate.year();

        if (ch::sys_days{startDate} + ch::years{1} >= ch::sys_days{endDate}) {
            ch::year_month currentMonth = startDate.year() / startDate.month();
            ch::year_month finalMonth = endDate.year() / endDate.month();

            while (currentMonth <= finalMonth) {
                ch::sys_seconds monthStart{ch::sys_days{currentMonth / 1}};
                ch::sys_seconds nextMonthStart{ch::sys_days{(currentMonth + ch::months{1}) / 1}};

                statistics::TimeRange range{monthStart, nextMonthStart};

                statistics::DataFrameView& dfv = m_dataPool.getDataFrameViewForRange(range);
                *set << (dfv.getTotalStreamingTime() / 3'600'000.0);
                categories << monthNames[static_cast<unsigned>(currentMonth.month()) - 1].data();

                currentMonth += ch::months{1};
            }

        } else {
            while (currentYear <= finalYear) {
                ch::sys_seconds yearStart{ch::sys_days{currentYear / ch::January / 1}};
                ch::sys_seconds nextYearStart{ch::sys_days{(currentYear + ch::years{1}) / ch::January / 1}};

                statistics::TimeRange range{yearStart, nextYearStart};

                statistics::DataFrameView dfv = m_dataPool.getDataFrameViewForRange(range);
                *set << (dfv.getTotalStreamingTime() / 3'600'000.0);
                categories << std::to_string(int(currentYear)).data();

                currentYear += ch::years{1};
            }
        }
    }

    void SmallTimeGraph::mousePressEvent(QMouseEvent* event) {
        if (event->button() == Qt::LeftButton) {
            emit cardClicked(m_stackIndex);
        }

        QWidget::mousePressEvent(event);
    }
    
} // namespace ui
