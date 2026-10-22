#include <iostream>

#include <QApplication>
#include <QFile>

#include "statistics/data_frame.hpp"
#include "statistics/data_frame_pool.hpp"
#include "ui/main_window.hpp"

using namespace ui;

int main(int argc, char** argv) {
    std::cout << argv[1] << std::endl;

    statistics::DataFrame df{argv[1]};
    statistics::DataFramePool dfp{};
    dfp.setData(std::move(df));

    QApplication app(argc, argv);

    QFile file{":/style.qss"};

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        app.setStyleSheet(QString::fromUtf8(file.readAll()));
    }

    MainWindow mainWindow{dfp};
    mainWindow.show();

    mainWindow.fillWithData();

    return app.exec();
}