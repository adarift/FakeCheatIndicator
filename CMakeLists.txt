cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(FakeCheatIndicator)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    libraries/gd.h
    libraries/gd.h/include
    libraries/minhook/include
)

add_subdirectory(libraries/minhook)
add_subdirectory(libraries/cocos-headers)

target_link_libraries(${PROJECT_NAME}
    minhook
    cocos2d
)