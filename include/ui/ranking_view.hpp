#pragma once

#include <string>
#include <QWidget>

#include "statistics/data_frame_pool.hpp"
#include "ui/big_view_base.hpp"

namespace ui
{
    class StatisticsView;
    class RankingView : public BigViewBase {
        Q_OBJECT

    public:
        explicit RankingView(statistics::DataFramePool& dataPool, StatisticsView* parentView, std::string&& name, QWidget* parent = nullptr);

        void fillWithData() override;

    private:
        std::string m_name;
    };
    
} // namespace ui
