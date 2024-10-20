find_path(XOCEANLIB_INCLUDE_DIR dependencies/xoceanlib/include 
                                ${CMAKE_SOURCE_DIR}/ModuleMode)
find_library(XOCEANLIB_LIBRARY 
                NAMES XOceanLib 
                PATHS dependencies/xoceanlib/build ${CMAKE_SOURCE_DIR}/ModuleMode)

if(XOCEANLIB_INCLUDE_DIR AND XOCEANLIB_LIBRARY)
    set(XOCEANLIB_FOUND TRUE)
endif()