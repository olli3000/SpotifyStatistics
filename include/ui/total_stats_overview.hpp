#pragma once

#include <QWidget>

#include "statistics/data_frame.hpp"

namespace ui
{
    class TotalStatsOverview : public QWidget {
        Q_OBJECT

    public:
        explicit TotalStatsOverview(statistics::DataFrame& data, QWidget* parent = nullptr);

    signals:
        void clicked();
    
    protected:
        void mousePressEvent(QMouseEvent* event) override;

    private:
        QWidget* createCard(const std::string& name, const std::string& data);
    };

} // namespace ui
