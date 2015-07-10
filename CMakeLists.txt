cmake_minimum_required(VERSION 3.2)
project(linAnil)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -std=c++11  -fpermissive")
add_definitions(-DNANOVG_GLEW -D_CRT_SECURE_NO_WARNINGS )
link_libraries(-lnanovg -lglfw3 -lglew32 -lopengl32 -lboost_filesystem-mt -lboost_system-mt)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(D:/msys64/mingw32/include)
# Find the QtWidgets library
#find_package(Qt5Widgets)
#find_package(Qt5OpenGL)
#find_package(Qt5Core)
#find_package(OpenGL)
#find_package(Qt5Multimedia REQUIRED)
# Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOMOC ON)


set(SOURCE_FILES main.cpp)
add_executable(linAnil ${SOURCE_FILES} view/MainWin.hpp model/TrackModel2.hpp view/ui.hpp view/win/FileDialog.hpp)
#target_link_libraries(linAnil Qt5::Widgets Qt5::Core Qt5::Multimedia)
