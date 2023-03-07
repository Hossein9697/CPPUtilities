cmake_minimum_required(VERSION 3.5)

project(Utilities VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Multimedia)

set(UTILITIES_DEPENDENCY $ENV{BTM_DPENDENCIES})

include_directories(
        ${UTILITIES_DEPENDENCY}/include
        ${UTILITIES_DEPENDENCY}/xfs/XFS_STANDARD_03/INCLUDE
)

file(GLOB utilities_src
        src/*/*.c
        src/*/*.cpp
        src/*/*/*.c
        src/*/*/*.cpp
        src/*/*/*/*.c
        src/*/*/*/*.cpp
        include/*/*.h
        include/*/*.hpp
        include/*/*/*.h
        include/*/*/*.hpp
        include/*/*/*/*.h
        include/*/*/*/*.hpp
        )

link_directories(
        ${UTILITIES_DEPENDENCY}/lib
        ${UTILITIES_DEPENDENCY}/xfs/XFS_STANDARD_03
        ${UTILITIES_DEPENDENCY}/xfs/XFS_STANDARD_03/LIB
)

qt_add_library(Utilities
        STATIC
        ${utilities_src}
        )

target_include_directories(Utilities
        PUBLIC
        include
        )

target_link_libraries(Utilities
        PUBLIC
        Qt6::Core
        Qt6::Multimedia

        MSXFS
        xfs_conf
        SSIDLL

        debug quazip1-qt6d.lib
        optimized quazip1-qt6.lib

        debug log4cplusUd.lib
        optimized log4cplusU.lib

        debug libcurl-d.lib
        optimized libcurl.lib

        debug zlibd.lib
        optimized zlib.lib
        )

qt_finalize_target(Utilities)

if (BUILD_TESTING)
    #add GoogleTest
    file(GLOB test_src test/*.cpp)
    add_executable(Utilities_Test ${test_src})
    target_link_libraries(Utilities_Test gtest_main Utilities)
    add_custom_command(TARGET Utilities_Test POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${UTILITIES_DEPENDENCY}/bin/$<CONFIGURATION>
            $<TARGET_FILE_DIR:Utilities_Test>
            )
endif (BUILD_TESTING)
