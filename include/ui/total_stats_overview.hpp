#pragma once

#include <QWidget>

#include "statistics/data_frame_pool.hpp"

namespace ui
{
    class TotalStatsOverview : public QWidget {
        Q_OBJECT

    public:
        explicit TotalStatsOverview(statistics::DataFramePool& dataPool, QWidget* parent = nullptr);

        void fillWithData();

    signals:
        void clicked();
    
    protected:
        void mousePressEvent(QMouseEvent* event) override;

    private:
        statistics::DataFramePool& m_dataPool;

        QWidget* m_songsCard;
        QWidget* m_artistsCard;
        QWidget* m_timeCard;

        QWidget* createCard();
        void fillCard(QWidget* card, const std::string& name, const std::string& data);
    };

} // namespace ui
