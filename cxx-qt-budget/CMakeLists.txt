cmake_minimum_required(VERSION 3.10)

file(STRINGS "version.txt" VERSION)

project(qtBudget VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#set(CMAKE_PREFIX_PATH $ENV{QTLib})
#set(CMAKE_PREFIX_PATH "C:/library/qt")

find_package(Qt5 REQUIRED COMPONENTS
        Core
        Gui
        Widgets
        Charts
)

include_directories(.)

add_definitions(-DVERSION="${PROJECT_VERSION}")
add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)
add_definitions(-DWIN32)
add_definitions(-DMINGW_HAS_SECURE_API=1)
add_definitions(-DQT_DEPRECATED_WARNINGS)
add_definitions(-DQT_NO_DEBUG)
add_definitions(-DQT_CORE_LIB)
add_definitions(-DQT_GUI_LIB)
add_definitions(-DQT_WIDGETS_LIB)
add_definitions(-DQT_CHARTS_LIB)

if(CMAKE_BUILD_TYPE MATCHES "Release")
    add_compile_options(-O2)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_options(-fexceptions)
    add_compile_options(-Wextra)
    add_compile_options(-Wall)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Release")
    add_link_options(-s)
    add_link_options(-mwindows)
endif()

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}-${PROJECT_VERSION})

target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/mainframe.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/graphdata.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/data.cpp)

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
)