cmake_minimum_required(VERSION 3.12)

project(ASCIIRasterizer)

set(CMAKE_CXX_STANDARD 20)              # or 20, 23, etc.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(X11 REQUIRED)

file(GLOB ASCIIRasterizer_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")
add_executable(ASCIIRasterizer ${ASCIIRasterizer_SRC})

target_link_libraries(ASCIIRasterizer PRIVATE X11::X11 ncurses)
