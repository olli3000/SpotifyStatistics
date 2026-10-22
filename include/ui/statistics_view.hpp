#pragma once

#include <QWidget>

#include "statistics/data_frame_pool.hpp"
#include "ui/small_view_card.hpp"
#include "ui/small_time_graph.hpp"
#include "ui/big_view_base.hpp"
#include "ui/ranking_view.hpp"

class QStackedWidget;
namespace ui
{
    class StatisticsView : public QWidget {
        Q_OBJECT

    public:
        explicit StatisticsView(statistics::DataFramePool& dataPool, QWidget* parent = nullptr);

        void fillWithData();

    public slots:
        void switchView(int index);
        void selectMainView();

    private:
        void createSmallView(QWidget* smallView);

        statistics::DataFramePool& m_dataPool;
        QStackedWidget* m_stack;

        SmallViewCard* m_topSongsCard;
        SmallViewCard* m_topArtistsCard;
        SmallViewCard* m_topAlbumsCard;
        SmallTimeGraph* m_smallTimeGraph;

        BigViewBase* m_bigSongsView;
        BigViewBase* m_bigArtistsView;
        BigViewBase* m_bigAlbumsView;
    };

} // namespace ui
