cmake_minimum_required(VERSION 3.9)
project(GtkmmPlayground)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "-x objective-c")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
link_directories(${GTK3_LIBRARY_DIRS})

pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)
include_directories(${GTKMM3_INCLUDE_DIRS})
list(APPEND Libs ${GTKMM3_LIBRARIES})

pkg_check_modules(GSTREAMERMM REQUIRED gstreamermm-1.0)
include_directories(${GSTREAMERMM_INCLUDE_DIRS})
list(APPEND Libs ${GSTREAMERMM_LIBRARIES})

list(APPEND Libs "resolv")

file(GLOB SOURCES src/*/*.cpp src/*/*.h src/*/*.m src/*/*.png)

include_directories(include)
include_directories(src/main)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${Libs})