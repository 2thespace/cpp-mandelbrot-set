cmake_minimum_required(VERSION 3.5)

project(mondelbort-set)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/out )

# find_package(JPEG REQUIRED)


add_subdirectory(thirdparty/cpp-image-converter/ImgLib)

add_executable(${PROJECT_NAME} src/main.cpp
    include/mondelbort_set.hpp src/mondelbort_set.cpp
)



include_directories(include/ thirdparty/cimg)

target_link_libraries(${PROJECT_NAME}
    ImgLib
)
