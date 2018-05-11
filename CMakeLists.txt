cmake_minimum_required (VERSION 2.6)
project (leica_localization)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#add_subdirectory(src)
find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

# add the executable
add_executable(leica_localization src/main.cpp)
target_link_libraries(leica_localization ${CERES_LIBRARIES})
