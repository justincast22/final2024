cmake_minimum_required(VERSION 3.29)
project(ResturantAppFinal)

set(CMAKE_CXX_STANDARD 14)

add_executable(main.cpp
        chef.cpp
        chef.h
        menu.h
        menu.cpp
        role.h
        role.cpp
        order.h
        order.cpp
        main.cpp
        OrderManager.h
        OrderManager.cpp
        receipt.cpp
        receipt.h
)
