cmake_minimum_required(VERSION 3.2)
project(linAnil)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -std=c++11 -fpermissive" )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPTW32_STATIC_LIB -fno-aggressive-loop-optimizations" )
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -static -std=c++11 -fpermissive" )
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -s -std=c++11 -fpermissive")
add_definitions(-DNANOVG_GLEW -D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DGLEW_STATIC)
add_definitions(-DGLEW_NO_GLU)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -Wl,-Bdynamic")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-Bstatic -lglew32")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-Bstatic -lnanovg")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-Bdynamic -lportaudio")

#link_libraries(-lnanovg -lopengl32)

#link_libraries(-lglew32 -lnanovg -lglfw3 -lopengl32 -lportaudio)
link_libraries( -lnanovg -lglew32 -lopengl32)
#link_libraries( -lavcodec -lavformat -lavutil)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-Bstatic -lavresample")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-Bstatic -lportaudio")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread  -Wl,-Bdynamic")

#link_libraries(-lnanovg -lglfw3 -lglew32 -lopengl32 -lportaudio)
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")
#find_package(Threads REQUIRED)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(view/ui)
include_directories(view)
include_directories(vs)
set(SOURCE_FILES main.cpp)
add_executable(linAnil ${SOURCE_FILES}
events/Evt.hpp
model/CompositionInfo.hpp
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
view/KeyInput.hpp
view/Stage.hpp
model/ImageLoader.hpp
view/timeline/Timeline.hpp
view/TitleBar.hpp
view/timeline/Track.hpp
view/timeline/TrackToolBar.hpp
view/Theme.hpp
vs/events/SpriteEvent.hpp
view/timeline/TimestampBar.hpp
model/ProjectInfo.hpp
view/PopupMenu.hpp
vs/Splitter.hpp
vs/Rect.hpp
vs/events/ErrorEvent.hpp
view/viewport/Viewport.hpp
vs/events/KeyEvent.hpp
view/tools/ColorWheel.hpp
model/AudioTrackInfo.hpp
#view/playback/portaudioTest.hpp
vs/VsGFX.hpp
vs/CommonMethod.hpp view/playback/FramesPlayback.hpp vs/utils/VsTimer.hpp vs/events/TimerEvent.hpp view/playback/PlaybackState.hpp
view/timeline/AudioTrack.hpp view/timeline/BaseTrack.hpp view/playback/AudioPlayback.hpp view/timeline/CompTabs.hpp vs/TextField.hpp
#view/playback/SDLtes1t.hpp
view/playback/WavPlayer.hpp
 view/playback/FFmpegTest.hpp test/Test.hpp view/playback/AudioPlayer.hpp test/Sndfile.hpp view/playback/BasePlayback.hpp)

set(LIB_DIR ${CMAKE_CXX_COMPILER}/../../lib)
#ADD_LIBRARY(portaudio_lib STATIC IMPORTED)
#SET_TARGET_PROPERTIES(portaudio_lib PROPERTIES
#    IMPORTED_LOCATION ${LIB_DIR}/libportaudio.a)
#TARGET_LINK_LIBRARIES(linAnil portaudio_lib)

#ADD_LIBRARY(glew_lib STATIC IMPORTED)
#SET_TARGET_PROPERTIES(glew_lib PROPERTIES
#    IMPORTED_LOCATION ${LIB_DIR}/libglew32.a)
##TARGET_LINK_LIBRARIES(linAnil glew_lib)
#
#ADD_LIBRARY(nanovg_lib STATIC IMPORTED)
#SET_TARGET_PROPERTIES(nanovg_lib PROPERTIES
#    IMPORTED_LOCATION ${LIB_DIR}/libnanovg.a)
#TARGET_LINK_LIBRARIES(linAnil nanovg_lib glew_lib )

target_link_libraries(linAnil :libboost_system-mt.a)
target_link_libraries(linAnil :libboost_filesystem-mt.a)
#target_link_libraries(linAnil :libsndfile.dll.a)
#target_link_libraries(linAnil :libglew32.a)
target_link_libraries(linAnil glew32)
target_link_libraries(linAnil glfw3)
target_link_libraries(linAnil nanovg)
#target_link_libraries(linAnil :libglfw3.a)
#target_link_libraries(linAnil :libnanovg.a)
target_link_libraries(linAnil sndfile)
target_link_libraries(linAnil portaudio)
#target_link_libraries(linAnil SDL2)
#target_link_libraries(linAnil SDL2_mixer)

#target_link_libraries(linAnil :libavcodec.a)
#target_link_libraries(linAnil :libavformat.a)
#target_link_libraries(linAnil :libavutil.a)
#target_link_libraries(linAnil avcodec)
#target_link_libraries(linAnil avformat)
#target_link_libraries(linAnil avutil)
#target_link_libraries(linAnil avresample)

#target_link_libraries(linAnil :avcodec.lib)
#target_link_libraries(linAnil :avformat.lib)
#target_link_libraries(linAnil :avutil.lib)
#target_link_libraries(linAnil :avfilter.lib)
#target_link_libraries(linAnil :swresample.lib)

#target_link_libraries(linAnil :libportaudio.a)
#target_link_libraries(linAnil :libportaudiocpp.a)

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
#sound
file(COPY ${BIN_DIR}/libportaudio-2.dll DESTINATION .)
file(COPY ${BIN_DIR}/avcodec-56.dll DESTINATION .)
file(COPY ${BIN_DIR}/libcelt0-2.dll DESTINATION .)
#file(COPY ${BIN_DIR}/libsndfile-1.dll DESTINATION .)
#file(COPY ${BIN_DIR}/libFLAC-8.dll DESTINATION .)
#file(COPY ${BIN_DIR}/libogg-0.dll DESTINATION .)
#file(COPY ${BIN_DIR}/libvorbis-0.dll DESTINATION .)
#file(COPY ${BIN_DIR}/libvorbisenc-2.dll DESTINATION .)
#file(COPY ${BIN_DIR}/OpenAL32.dll DESTINATION .)

#copy res
file(GLOB FONTS "vs/fonts/*.ttf")
file(COPY ${FONTS} DESTINATION fonts)
file(GLOB THUMBS "test/thumb/*.jpg")
file(COPY ${THUMBS} DESTINATION test/thumb)
file(COPY oui/DejaVuSans.ttf oui/blender_icons16.png oui/blender_icons.svg DESTINATION oui)
