cmake_minimum_required (VERSION 2.6)
project (trilateration)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)

#add_subdirectory(src)
find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

# add the executable
add_executable(trilateration src/main.cpp src/solver.cpp)
target_link_libraries(trilateration ${CERES_LIBRARIES})
