# SpotifyStatistics
A visualizer for your Spotify streaming history

You can request your data on Spotify and it will send you a zip folder with the json files about your streaming history.

## Requirements:
Ubuntu 22

GCC 12.3.0

C++20

Qt 6.2.4

CMake 3.22.1

## How to build:
In root directory do:

```
cmake -S . -B build
```

then

```
cmake --build build --target Spotify_Statistics
```

and finally run the app with

```
./build/Spotify_Statistics <path-to-directory-with-json-files>
```
