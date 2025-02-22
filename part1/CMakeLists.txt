cmake_minimum_required(VERSION 3.22)
set(BOARD esp32_devkitc_wroom/esp32/procpu)

find_package(Zephyr)

project(hello_world_yttut)
target_sources(app PRIVATE src/main.c)
