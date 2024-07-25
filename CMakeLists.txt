project(XOceanLib VERSION 0.0.1 beta)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 99)
# set(CMAKE_C_STANDARD_REQUIRED ON)

string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%d %H:%M:%S")


find_package(mimalloc REQUIRED)

# mimalloc 
# add_subdirectory(runtime/mimalloc)
# target_link_libraries(${PROJECT_NAME} PUBLIC mimalloc)

include(basic_env)
include_directories(${PROJECT_SOURCE_DIR}/include)

configure_file(XOceanLibConfig.h.in cm-config.h)

target_include_directories(${PROJECT_NAME} PUBLIC
                           ${PROJECT_BINARY_DIR})
                           #${PROJECT_SOURCE_DIR}/mimalloc)
                           
target_link_libraries(XOceanLib PRIVATE mimalloc)
