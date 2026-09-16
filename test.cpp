#include <iostream>
// #include <chrono>
// #include <string>
// #include <vector>
// #include <fstream>
// #include <nlohmann/json.hpp>
// #include <filesystem>

// using json = nlohmann::json;

#include <QApplication>
#include <QFile>
// #include <QVBoxLayout>

// #include <QChartView>
// #include <QChart>
// #include <QLineSeries>

// #include <QBarSet>
// #include <QBarSeries>
// #include <QBarCategoryAxis>

// #include <QMainWindow>
// #include <QMenuBar>
// #include <QToolBar>
// #include <QDockWidget>
// #include <QPushButton>

// #include <QScreen>
// #include <QWindow>

#include "ui/main_window.hpp"
#include "ui/window.hpp"

using namespace ui;

int main(int argc, char** argv) {

    QApplication app(argc, argv);

    QFile file{":/style.qss"};

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        app.setStyleSheet(QString::fromUtf8(file.readAll()));
    }

    MainWindow mainWindow;
    mainWindow.show();

    // QMainWindow mainWindow;
    // mainWindow.setWindowTitle("Spotify Statistics");
    // mainWindow.setMinimumSize(1280, 720);
    // mainWindow.setWindowState(mainWindow.windowState());// ^ Qt::WindowMaximized);

    // mainWindow.menuBar()->addMenu(QObject::tr("&File"));
    // mainWindow.menuBar()->addMenu(QObject::tr("&Edit"));

    // QWidget centralWidget{&mainWindow};
    // mainWindow.setCentralWidget(&centralWidget);
    // centralWidget.setContentsMargins(20, 20, 20, 20);

    // QPushButton button{"Test", &centralWidget};

    // QScreen *screen = QGuiApplication::primaryScreen();

    // mainWindow.setGeometry(screen->availableGeometry());
    // mainWindow.show();
    // mainWindow.maxim;

    // Window window;
    // window.show();

    // QWidget window;
    // window.setFixedSize(400, 160);

    // QProgressBar *progressBar = new QProgressBar(&window);
    // progressBar->setRange(0, 100);
    // progressBar->setValue(0);
    // progressBar->setGeometry(20, 20, 360, 60);

    // QSlider *slider = new QSlider(&window);
    // slider->setOrientation(Qt::Horizontal);
    // slider->setRange(0, 100);
    // slider->setValue(0);
    // slider->setGeometry(20, 80, 360, 60);

    // window.show();

    // QObject::connect(slider, SIGNAL(valueChanged(int)), progressBar, SLOT(setValue(int)));

    // QWidget window;
    // window.setBaseSize(800, 600);

    // QLineSeries *series = new QLineSeries();

    // series->append(0, 120);
    // series->append(1, 145);
    // series->append(2, 132);
    // series->append(3, 178);
    // series->append(4, 201);
    // series->append(5, 190);

    // QChart *chart = new QChart();
    // chart->addSeries(series);
    // chart->setTitle("Songs played per month");

    // QChartView *chartView = new QChartView(chart);
    // chartView->setRenderHint(QPainter::Antialiasing);


    // QBarSet *set = new QBarSet("Plays");
    // *set << 250 << 190 << 170 << 150 << 130;

    // QBarSeries *barSeries = new QBarSeries();
    // barSeries->append(set);

    // QChart *barChart = new QChart();
    // barChart->addSeries(barSeries);
    // barChart->setTitle("Top Artists");

    // QStringList categories;
    // categories << "Taylor Swift" << "Daft Punk" << "The Weeknd" << "Linkin Park" << "Robin Schulz";

    // QBarCategoryAxis *axis = new QBarCategoryAxis();
    // axis->append(categories);

    // barChart->addAxis(axis, Qt::AlignBottom);
    // barSeries->attachAxis(axis);

    // QChartView *barChartView = new QChartView(barChart);
    // barChartView->setRenderHint(QPainter::Antialiasing);


    // QVBoxLayout *layout = new QVBoxLayout(&window);
    // layout->addWidget(chartView);
    // layout->addWidget(barChartView);

    // window.show();

    return app.exec();

    // std::cout << "Hi from test\n";
}