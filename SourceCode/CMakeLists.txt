cmake_minimum_required(VERSION 3.0.0)
project(OSA2 VERSION 0.1.0)


add_executable(OSA2 main.cpp)

target_link_libraries(OSA2 SDL2main SDL2 SDL2_image SDL2_ttf )
target_link_libraries(OSA2 pthread)

