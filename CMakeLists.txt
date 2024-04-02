cmake_minimum_required(VERSION 3.24.0 FATAL_ERROR)
project(ip-labs-macos
        VERSION 0.1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenCV REQUIRED)

add_definitions(-DASSETS_DIR="${CMAKE_SOURCE_DIR}/assets/")

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/3rdparty/nativefiledialog-extended")

add_executable(${PROJECT_NAME}
        src/util/file-util.cpp
        src/util/image-util.cpp
        src/labs/lab.cpp
        src/labs/lab1.cpp
        src/labs/lab2.cpp
        src/main.cpp
        src/labs/lab3.cpp
        include/labs/lab3.hh
        include/labs/lab4.hh
        src/labs/lab4.cpp
        include/labs/lab5.hh
        src/labs/lab5.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include/labs ${CMAKE_CURRENT_LIST_DIR}/include/util)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS} nfd)
