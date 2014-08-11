cmake_minimum_required (VERSION 3.0)
project (QuadTreeTest)

include_directories("${PROJECT_BINARY_DIR}/include")

add_executable(QuadTreeTest main.cpp src/QuadTree.cpp src/CollisionEngine.cpp src/Timer.cpp src/Particle.cpp)
target_link_libraries (QuadTreeTest SDL2)
