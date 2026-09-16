#pragma once

#include <QMainWindow>

#include "statistics/data_frame.hpp"

class QWidget;
class QLabel;

namespace ui 
{
    class MainWindow : public QMainWindow {
        Q_OBJECT
        
    public:
        explicit MainWindow(statistics::DataFrame& data, QWidget *parent = nullptr);

    private:
        QWidget* m_centralWidget;
        QLabel* m_title;
    };

} // namespace ui
