cmake_minimum_required(VERSION 3.16)

project(BMPModifier LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BMPModifier main.cpp
    BMPModifier.h BMPModifier.cpp)

include(GNUInstallDirs)
install(TARGETS BMPModifier
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
