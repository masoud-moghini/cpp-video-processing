cmake_minimum_required(VERSION 3.14)
project(video C CXX)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(libs/FFMpeg)
add_subdirectory(libs/glfw)


if(APPLE)
list(APPEND EXTRA_LIBS)        

else()
list(APPEND EXTRA_LIBS "-lGL  -lX11")
endif()


list(APPEND SOURCES
        src/main.cpp
        src/load_frame.hpp
        src/load_frame.cpp
)

add_executable(video ${SOURCES})

target_link_libraries(video  FFMpeg glfw ${EXTRA_LIBS}) 