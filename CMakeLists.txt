cmake_minimum_required(VERSION 3.0)
project( recon )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( recon ./src/main.cpp )
set_target_properties( recon
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
)

target_link_libraries( recon ${OpenCV_LIBS} )
