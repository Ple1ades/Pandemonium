cmake_minimum_required(VERSION 3.0.0)
project(Pandemonium VERSION 0.1.0)
INCLUDE_DIRECTORIES(
    C:/Pleiades/vcpkg/installed/x64-windows/include/
)

LINK_DIRECTORIES(
    C:/Pleiades/vcpkg/installed/x64-windows/lib/
)
add_executable(Pandemonium main.cpp)
find_package(box2d CONFIG REQUIRED)
target_link_libraries(Pandemonium PRIVATE
    box2d::box2d SDL2
)
include(CTest)
enable_testing()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
include(CPack)
