cmake_minimum_required(VERSION 3.16)
project(my_c C)

set(CMAKE_C_STANDARD 99)


file(GLOB CPP_RESOURCE
        LeetCode/*.c
        )
file(GLOB DEMO_RESOURCE
        进程间通信IPC/*.c
        )

# 遍历可运行的代码目录，并将这些文件添加到可运行里边
foreach(FILE_PATH ${CPP_RESOURCE})
    STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FILE_PATH})
    add_executable(${FILE_NAME} ${FILE_PATH} )
endforeach()

# 你有多少个可运行的目录，就需要遍历几次
foreach(FILE_PATH ${DEMO_RESOURCE})
    STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FILE_PATH})
    add_executable(${FILE_NAME} ${FILE_PATH})
endforeach()


# add_executable(my_c unix/03标准io/main.c)