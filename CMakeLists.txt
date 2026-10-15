cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Spotify_Statistics)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Charts)

set(FILES
    src/statistics/data_frame_view.cpp
    src/statistics/data_frame.cpp
    src/statistics/song_history.cpp

    include/ui/main_window.hpp # else AUTOMOC has some skill issue
    include/ui/total_stats_overview.hpp
    include/ui/statistics_view.hpp
    include/ui/small_view_card.hpp
    include/ui/small_time_graph.hpp

    src/ui/main_window.cpp
    src/ui/total_stats_overview.cpp
    src/ui/statistics_view.cpp
    src/ui/small_view_card.cpp
    src/ui/small_time_graph.cpp

    resources/resources.qrc
)

qt_add_executable(Spotify_Statistics main.cpp ${FILES})
qt_add_executable(Test test.cpp ${FILES})

target_include_directories(Spotify_Statistics PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(Test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(Spotify_Statistics PRIVATE Qt6::Core Qt6::Widgets Qt6::Charts)
target_link_libraries(Test PRIVATE Qt6::Core Qt6::Widgets Qt6::Charts)

target_compile_options(Spotify_Statistics PRIVATE -Wall -Werror -O3)
target_compile_options(Test PRIVATE -Wall -Werror -Wno-unused-variable -O3)
