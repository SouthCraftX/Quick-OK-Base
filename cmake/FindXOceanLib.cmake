find_path(QOEANLIB_INCLUDE_DIR ./include ${CMAKE_SOURCE_DIR}/ModuleMode)
find_library(QOEANLIB_LIBRARY 
                NAMES XOceanLib 
                PATHS ./build ${CMAKE_SOURCE_DIR}/ModuleMode)

if(QOEANLIB_INCLUDE_DIR AND QOEANLIB_LIBRARY)
    set(QOEANLIB_FOUND TRUE)
endif()