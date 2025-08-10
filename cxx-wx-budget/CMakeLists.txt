cmake_minimum_required(VERSION 3.10)

file(STRINGS "version" VERSION)

project(wxBudget VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(wxWidgets_LIB_DIR $ENV{WXWIN}/lib/gcc_libx64)

find_package(wxWidgets 3 REQUIRED propgrid xml core base)

execute_process(
    COMMAND CMD /c git rev-parse --short HEAD
    OUTPUT_VARIABLE GIT_HASH
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

#add_definitions(-DCOMMIT="${GIT_HASH}")
add_definitions(-DVERSION="${PROJECT_VERSION}")
add_definitions(-DHAVE_W32API_H)
add_definitions(-D__WXMSW__)
add_definitions(-D_UNICODE)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DSTAND_DEBUG)
    add_definitions(-DSTAND_DEBUG_EXCHANGE_DATA)
elseif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    add_definitions(-DSTAND_DEBUG)
    add_definitions(-DSTAND_DEBUG_EXCHANGE_DATA)
    add_definitions(-DNDEBUG)
else()
    add_definitions(-DNDEBUG)
endif()

include_directories(.)
include_directories(src)
include_directories(${wxWidgets_INCLUDE_DIRS})

add_compile_options(-funsigned-bitfields)
add_compile_options(-O0)
add_compile_options(-Wall)
add_compile_options(-mthreads)
add_compile_options(-Wno-ctor-dtor-privacy)
add_compile_options(-pipe)
add_compile_options(-fmessage-length=0)
add_compile_options(-mno-ms-bitfields)

add_link_options(-mthreads)
add_link_options(-static-libgcc)
add_link_options(-static-libstdc++)

if(CMAKE_BUILD_TYPE MATCHES Debug)

elseif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    add_link_options(-s)
else()
    add_link_options(-s)
    add_link_options(-mwindows)
endif()

link_directories(${wxWidgets_LIB_DIR})

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    OUTPUT_NAME Budget-${CMAKE_BUILD_TYPE}-${PROJECT_VERSION}
)

target_sources(${PROJECT_NAME} PRIVATE src/res/resource.rc)
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/ui/mainframe.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/ui/bankspanel.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/ui/mortgagepanel.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/utils/utils.cpp)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxmsw33u_propgrid)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxmsw33u_richtext)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxmsw33u_xrc)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxmsw33u_aui)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxmsw33u_html)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxmsw33u_adv)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxmsw33u_core)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxbase33u_xml)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxbase33u_net)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxbase33u)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxscintilla)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxtiff)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxjpeg)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxpng)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxzlib)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxregexu)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxexpat)
    target_link_libraries(${PROJECT_NAME} PRIVATE kernel32)
    target_link_libraries(${PROJECT_NAME} PRIVATE user32)
    target_link_libraries(${PROJECT_NAME} PRIVATE gdi32)
    target_link_libraries(${PROJECT_NAME} PRIVATE comdlg32)
    target_link_libraries(${PROJECT_NAME} PRIVATE wxregexu)
    target_link_libraries(${PROJECT_NAME} PRIVATE winspool)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm)
    target_link_libraries(${PROJECT_NAME} PRIVATE shell32)
    target_link_libraries(${PROJECT_NAME} PRIVATE comctl32)
    target_link_libraries(${PROJECT_NAME} PRIVATE version)
    target_link_libraries(${PROJECT_NAME} PRIVATE shlwapi)
    target_link_libraries(${PROJECT_NAME} PRIVATE ole32)
    target_link_libraries(${PROJECT_NAME} PRIVATE oleaut32)
    target_link_libraries(${PROJECT_NAME} PRIVATE uuid)
    target_link_libraries(${PROJECT_NAME} PRIVATE rpcrt4)
    target_link_libraries(${PROJECT_NAME} PRIVATE advapi32)
    target_link_libraries(${PROJECT_NAME} PRIVATE wsock32)
    target_link_libraries(${PROJECT_NAME} PRIVATE uxtheme)
    target_link_libraries(${PROJECT_NAME} PRIVATE oleacc)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})
endif()