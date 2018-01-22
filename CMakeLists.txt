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

# vlc 库
find_package(LIBVLC REQUIRED)
include_directories(${LIBVLC_INCLUDE_DIR})
list(APPEND Libs ${LIBVLC_LIBRARY})
list(APPEND Libs ${LIBVLCCORE_LIBRARY})
list(APPEND Libs "resolv")

file(GLOB SOURCES src/*/*.cpp src/*/*.h src/*/*.m src/*/*.png)

include_directories(include)
include_directories(src/main)

add_executable(${PROJECT_NAME} ${SOURCES})
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_SOURCE_DIR}/cmake/FixBundle.sh ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY} ${CMAKE_BINARY_DIR} ${PROJECT_NAME}
        COMMENT "Fixing application bundle for local run"
        )

target_link_libraries(${PROJECT_NAME} ${Libs})