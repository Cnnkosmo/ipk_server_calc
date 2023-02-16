cmake_minimum_required(VERSION 3.24)
project(ipk23 C)

set(CMAKE_C_STANDARD 11)

add_executable(ipk23
        client_side.c
        server_side.c ipkcpc.c)
