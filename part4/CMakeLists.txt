cmake_minimum_required(VERSION 3.31)
set(BOARD esp32_devkitc_wroom/esp32/procpu)
set(DTC_OVERLAY_FILE "esp32.overlay")
find_package(Zephyr)
project(hello_world_blinky)

target_sources(app PRIVATE src/main.c)
