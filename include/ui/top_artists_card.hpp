#pragma once

#include <QWidget>

#include "statistics/data_frame.hpp"

namespace ui
{
    class TopArtistsCard : public QWidget {
        Q_OBJECT

    public:
        explicit TopArtistsCard(statistics::DataFrame& data, int stackIndex, QWidget* parent = nullptr);

    signals:
        void cardClicked(int index);

    protected:
        void mousePressEvent(QMouseEvent* event) override;

    private:
        QWidget* createEntry(int place, const std::string_view& name, long listeningTime);
        
        int m_stackIndex;
    };
    
} // namespace ui
