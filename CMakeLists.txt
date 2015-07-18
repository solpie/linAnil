cmake_minimum_required(VERSION 3.2)
project(linAnil)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -std=c++11 -fpermissive")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -s -std=c++11 -fpermissive")
add_definitions(-DNANOVG_GLEW -D_CRT_SECURE_NO_WARNINGS)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")
#dynamic link
#link_libraries(-lnanovg -lglfw3 -lglew32.dll -lopengl32)

link_libraries(-lnanovg -lglfw3 -lglew32 -lopengl32)
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")
#find_package(Threads REQUIRED)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(view/ui)
include_directories(view)
include_directories(vs)
set(SOURCE_FILES main.cpp)

add_executable(linAnil ${SOURCE_FILES}
events/Event.hpp
model/TrackModel.hpp
model/TrackInfo.hpp
model/TrackFrameInfo.hpp
model/FileWatcher.hpp
model/App.hpp
utils/Linker.hpp
events/ActionEvent.hpp
events/TrackModelEvent.hpp
vs/VsObj.hpp
vs/Performance.hpp
vs/VsObjContainer.hpp
vs/VsContext.hpp
vs/events/EventDispatcher.hpp
vs/Sprite.hpp
vs/events/MouseEvent.hpp
vs/events/BaseEvent.hpp
vs/Slider.hpp
vs/CheckBox.hpp
vs/events/VsEvent.hpp
vs/VsColor.hpp
vs/ScrollBar.hpp
view/UI.hpp
view/win/FileDialog.hpp
view/Input.hpp
view/UiRoot.hpp
view/TrackArea.hpp
view/timeline/Timeline.hpp
view/TitleBar.hpp
view/timeline/Track.hpp
view/timeline/TrackToolBar.hpp
view/Theme.hpp
vs/events/SpriteEvent.hpp view/timeline/TimestampBar.hpp model/ProjectInfo.hpp view/PopupMenu.hpp vs/Splitter.hpp vs/Rect.hpp vs/events/ErrorEvent.hpp view/viewport/Viewport.hpp)

target_link_libraries(linAnil :libboost_system-mt.a)
#target_link_libraries(linAnil :libwinpthread.a)
#target_link_libraries(linAnil :libglew32.dll.a)
#target_link_libraries(linAnil :libglew32.a)
#target_link_libraries(linAnil :libglfw3.dll.a)
#target_link_libraries(linAnil :libnanovg.a)
#target_link_libraries (linAnil ${CMAKE_THREAD_LIBS_INIT})
#COPY dll
set(BIN_DIR ${CMAKE_CXX_COMPILER}/../../bin)
file(COPY ${BIN_DIR}/libwinpthread-1.dll DESTINATION .)
file(COPY ${BIN_DIR}/glew32.dll DESTINATION .)
file(COPY ${BIN_DIR}/glfw3.dll DESTINATION .)

#copy res
file(GLOB FONTS "vs/fonts/*.ttf")
file(COPY ${FONTS} DESTINATION fonts)
file(GLOB THUMBS "test/thumb/*.jpg")
file(COPY ${THUMBS} DESTINATION test/thumb)
file(COPY oui/DejaVuSans.ttf oui/blender_icons16.png oui/blender_icons.svg DESTINATION oui)
