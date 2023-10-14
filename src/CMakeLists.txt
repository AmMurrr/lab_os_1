cmake_minimum_required(VERSION 3.10)
project(lab_os_1)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)


add_executable(child child.c)
set(REQUIRED_FILES child)
add_executable(main main.c)
