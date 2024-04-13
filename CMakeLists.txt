cmake_minimum_required(VERSION 3.8)
project(Explosion VERSION 0.1.0 LANGUAGES C CXX)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)

include(CTest)
enable_testing()

add_executable(Explosion Main.cpp Engine.cpp)

target_include_directories(Explosion PRIVATE "include")

target_link_libraries(Explosion PRIVATE sfml-system sfml-graphics sfml-window)
target_link_libraries(Explosion PRIVATE box2d::box2d)

# Copia degli assete e delle risorse

set(ASSETS_DIR "assets")

file(COPY ${ASSETS_DIR} DESTINATION ${PROJECT_BINARY_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
