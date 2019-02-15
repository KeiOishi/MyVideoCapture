cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR
            "CMake generation is not possible within the source directory!"
            "\n Remove the CMakeCache.txt file and try again from another folder, e.g.:"
            "\n "
            "\n rm CMakeCache.txt"
            "\n mkdir build"
            "\n cd build"
            "\n cmake .."
            )
endif()

find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    #    link_directories (${OpenCV_LIBS})
    message(STATUS "OpenCV version: ${OpenCV_VERSION}")
    message(STATUS "OpenCV libraries : ${OpenCV_LIBS}")
    message(STATUS "OpenCV directory : ${OpenCV_INCLUDE_DIRS}")
    link_libraries(${OpenCV_LIBS})
else()
    message(WARNING "Could not find OpenCV.")
endif()

set(PACKAGE_NAME "MyVideoCapture")
set(PACKAGE_VERSION "1.0")

add_subdirectory(web_camera)

include_directories(web_camera)

add_executable(main main.cpp)
target_link_libraries(main web)
install(TARGETS main DESTINATION bin)


