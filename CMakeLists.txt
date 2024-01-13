cmake_minimum_required (VERSION 3.0)
project (Secure-ML)
set(NAME "Secure-ML")
set (CMAKE_CXX_STANDARD 11)
find_path(CMAKE_FOLDER NAMES cmake/emp-tool-config.cmake)
include(${CMAKE_FOLDER}/cmake/common.cmake)
include(${CMAKE_FOLDER}/cmake/source_of_randomness.cmake)
include(${CMAKE_FOLDER}/cmake/threading.cmake)
find_package(emp-ot REQUIRED)
find_package(Eigen3 REQUIRED NO_MODULE)
INCLUDE_DIRECTORIES(${EMP-OT_INCLUDE_DIRS})

set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
# set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# add_executable(ideal_functionality
#     src/ideal_functionality.cpp
#     src/util.cpp
# )
# add_executable(secure_ML
#     src/secure_ML.cpp
#     src/linear_regression.cpp
#     src/online_phase.cpp
#     src/setup_phase.cpp
#     src/util.cpp
# )
add_executable(matrix_generate
    src/matrix_generate_main.cpp
    src/matrix_generate_setup.cpp
    src/online_phase.cpp
    src/util.cpp
)

# target_link_libraries(ideal_functionality ${EMP-OT_LIBRARIES} Eigen3::Eigen)
# target_link_libraries(secure_ML ${EMP-OT_LIBRARIES} Eigen3::Eigen)
target_link_libraries(matrix_generate ${EMP-OT_LIBRARIES} Eigen3::Eigen)