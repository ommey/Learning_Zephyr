cmake_minimum_required(VERSION 3.22)
set(BOARD esp32_devkitc_wroom/esp32/procpu)
set(DTC_OVERLAY_FILE "esp32.overlay") #ska läggas till vid overlay filen innan find package

find_package(Zephyr)

project(part2)
target_sources(app PRIVATE src/main.c)
