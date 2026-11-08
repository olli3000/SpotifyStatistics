#pragma once

#include <string>
#include <vector>
#include <QWidget>
#include <QScrollArea>

#include "statistics/data_frame_view.hpp"
#include "statistics/data_frame_pool.hpp"
#include "statistics/util.hpp"
#include "ui/big_view_base.hpp"

namespace ui
{
    class StatisticsView;

    template <typename DataFunc, typename GetName>
    class RankingView : public BigViewBase {

    public:
        explicit RankingView(statistics::DataFramePool& dataPool, StatisticsView* parentView, std::string&& name, DataFunc dataFunc, GetName getName, QWidget* parent = nullptr) 
            : BigViewBase(dataPool, parentView, parent), m_name(std::move(name)), dataFunc(dataFunc), getName(getName) {
            init();
        }

        void fillWithData() override;
        void fillWithData(statistics::TimeRange& timeRange) override;

    private:
        std::string m_name;
        QScrollArea* m_scrollArea;
        QVBoxLayout* m_contentLayout;

        DataFunc dataFunc;
        GetName getName;

        void init();
        QWidget* createEntry(int place, const std::string_view& name, long listeningTime);
    };
    
} // namespace ui

#include "ui/ranking_view.tpp"
