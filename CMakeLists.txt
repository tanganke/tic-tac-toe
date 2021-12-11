project(tic-tac-toe)
cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "src/*.cpp")
add_executable(tic-tac-toe 
  ${SOURCES}
)
target_include_directories(tic-tac-toe PRIVATE 
  "src")
target_link_libraries(tic-tac-toe
  fmt boost_timer
)
