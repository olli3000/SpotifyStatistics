#pragma once

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

namespace ui
{
    template <typename DataFunc, typename GetName>
    void RankingView<DataFunc, GetName>::init() {
        m_scrollArea = new QScrollArea();
        m_scrollArea->setWidgetResizable(true);


        QWidget* contentWidget = new QWidget();
        m_contentLayout = new QVBoxLayout();

        contentWidget->setLayout(m_contentLayout);
        m_scrollArea->setWidget(contentWidget);

        layout()->addWidget(m_scrollArea);
    }

    template <typename DataFunc, typename GetName>
    void RankingView<DataFunc, GetName>::fillWithData() {
        m_contentLayout->addWidget(new QLabel("Test"));
        auto data = dataFunc(m_dataPool.getDataFrameViewForRange());

        int i = 1;
        for (auto& entry : data) {
            m_contentLayout->addWidget(createEntry(i, getName(entry), entry.listeningTime));
            i++;
        }
    }

    template <typename DataFunc, typename GetName>
    void RankingView<DataFunc, GetName>::fillWithData(statistics::TimeRange& timeRange) {

    }

    template <typename DataFunc, typename GetName>
    QWidget* RankingView<DataFunc, GetName>::createEntry(int place, const std::string_view& name, long listeningTime) {
        QWidget* strip = new QWidget();

        QHBoxLayout* layout = new QHBoxLayout(strip);

        layout->addWidget(new QLabel(std::to_string(place).data(), strip));
        layout->addWidget(new QLabel(name.data(), strip));
        layout->addStretch();
        layout->addWidget(new QLabel(QString("%1 %2").arg(std::to_string(listeningTime / 3'600'000.0).data()).arg("h"), strip));

        return strip;
    }
    
} // namespace ui
