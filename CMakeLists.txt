cmake_minimum_required(VERSION 3.2)
project(linAnil)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -std=c++11 -pthread -fpermissive")
add_definitions(-DNANOVG_GLEW -D_CRT_SECURE_NO_WARNINGS )
link_libraries(-lnanovg -lglfw3 -lglew32 -lopengl32 -lboost_filesystem-mt -lboost_system-mt)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#include_directories(D:/msys64/mingw32/include)
#include_directories(SYSTEM mingw32/include)
include_directories(view/ui)

set(SOURCE_FILES main.cpp)
file(GLOB FONTS "vs/fonts/*.ttf")
file(COPY oui/DejaVuSans.ttf oui/blender_icons16.png oui/blender_icons.svg DESTINATION oui)
file(COPY ${FONTS} DESTINATION fonts)
add_executable(linAnil ${SOURCE_FILES}
view/VsRoot.hpp
events/Event.hpp
model/TrackModel2.hpp
model/TrackInfo.hpp
model/TrackFrameInfo.hpp
model/FileWatcher.hpp
view/ui.hpp
view/win/FileDialog.hpp view/Input.hpp view/Performance.hpp vs/VsObj.hpp vs/VsObjContainer.hpp vs/VsContext.hpp vs/EventDispatcher.hpp)
