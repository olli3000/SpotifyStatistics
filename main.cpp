#include <iostream>

#include <QApplication>
#include <QFile>

// #include "include/json_data_entry.hpp"
// #include "include/song_history.hpp"
#include "statistics/data_frame.hpp"
#include "ui/main_window.hpp"

// using json = nlohmann::json;
using namespace ui;

int main(int argc, char** argv) {
    std::cout << argv[1] << std::endl;

    statistics::DataFrame df{argv[1]};

    QApplication app(argc, argv);

    QFile file{":/style.qss"};

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        app.setStyleSheet(QString::fromUtf8(file.readAll()));
    }

    MainWindow mainWindow{df};
    mainWindow.show();

    // df.print();

    return app.exec();
}