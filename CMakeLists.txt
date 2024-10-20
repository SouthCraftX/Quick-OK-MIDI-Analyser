PROJECT(QOMA)

cmake_minimum_required(VERSION 3.17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
find_package(PkgConfig REQUIRED)
find_package(XOceanLib REQUIRED)
find_package(OpenGL EGL REQUIRED)
find_package(Freetype REQUIRED)
find_package(xxHash REQUIRED)

pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
    libavdevice
    libavfilter
    libavformat
    libavcodec
    libswresample
    libswscale
    libavutil
)
target_link_libraries(${PROJECT_NAME} PkgConfig::LIBAV)

if(XOceanLib_FOUND)
    include_directories(${XOceanLib_INCLUDE_DIRS})
    target_link_libraries(${XOceanLib_LIBRARIES})
else(XOceanLib_FOUND)
    message(FATAL_ERROR "XOceanLib not found")
endif(XOceanLib_FOUND)

if(OpenGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
else(OpenGL_FOUND)
    message(FATAL_ERROR "OpenGL not found")
endif(OpenGL_FOUND)

if(xxHash_FOUND)
    include_directories(${xxHash_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${xxHash_LIBRARIES})
else(xxHash_FOUND)
    message(FATAL_ERROR "xxHash not found")
endif(xxHash_FOUND)

if(Freetype_FOUND)
    include_directories(${FREETYPE_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})
else(Freetype_FOUND)
    message(FATAL_ERROR "Freetype not found")
endif(Freetype_FOUND)