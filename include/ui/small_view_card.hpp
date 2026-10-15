#pragma once

#include <QWidget>
#include <QString>
#include <QVBoxLayout>

#include "statistics/data_frame_view.hpp"

namespace ui
{
    class SmallViewCard : public QWidget {
        Q_OBJECT

    public:
        explicit SmallViewCard(const QString& title, int stackIndex, QWidget* parent = nullptr);

        template <typename Entry, typename GetName>
        void fillData(std::vector<Entry> entries, GetName getName) {
            int i = 0;
            for (auto& entry : entries) {
                if (i == 5) break;

                i++;
                m_contentLayout->addWidget(createEntry(i, getName(entry), entry.listeningTime));
            }
        }

    signals:
        void cardClicked(int index);

    protected:
        void mousePressEvent(QMouseEvent* event) override;

    private:
        int m_stackIndex;

        QVBoxLayout* m_contentLayout;

        QWidget* createEntry(int place, const std::string_view& name, long listeningTime);

    };

} // namespace ui


