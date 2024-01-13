project(XOceanLib VERSION 0.0.1 beta)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%d %H:%M:%S")

# mimalloc 
add_subdirectory(runtime/mimalloc)
target_link_libraries(${PROJECT_NAME} PUBLIC mimalloc)

configure_file(XOceanLibConfig.h.in cm-config.h)

target_include_directories(${PROJECT_NAME} PUBLIC
                           ${PROJECT_BINARY_DIR}
                           ${PROJECT_SOURCE_DIR}/mimalloc)
                           

