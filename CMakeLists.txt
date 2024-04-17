cmake_minimum_required(VERSION 2.8.3)
project(unitree_legged_sdk)

include_directories(include)

link_directories(lib)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3")

execute_process(COMMAND
  uname -m
  COMMAND tr -d '\n'
  OUTPUT_VARIABLE ARCHITECTURE
)

if(${ARCHITECTURE} STREQUAL "x86_64")
  set(LIBRARY_FILE libunitree_legged_sdk_amd64.so)
elseif(${ARCHITECTURE} STREQUAL "aarch64")
  set(LIBRARY_FILE libunitree_legged_sdk_arm64.so)
elseif(${ARCHITECTURE} STREQUAL "armv7l")
  set(LIBRARY_FILE libunitree_legged_sdk_arm32.so)
else()
  message(FATAL_ERROR "Unsupported architecture: ${ARCHITECTURE}")
endif()

set(EXTRA_LIBS -pthread rt m ${LIBRARY_FILE} lcm)

# one pc one process
add_executable(example_position examples/example_position.cpp)
target_link_libraries(example_position ${EXTRA_LIBS})

add_executable(example_velocity examples/example_velocity.cpp)
target_link_libraries(example_velocity ${EXTRA_LIBS})

add_executable(example_torque examples/example_torque.cpp)
target_link_libraries(example_torque ${EXTRA_LIBS})

add_executable(example_walk examples/example_walk.cpp)
target_link_libraries(example_walk ${EXTRA_LIBS})

add_executable(example_dance examples/example_dance.cpp)
target_link_libraries(example_dance ${EXTRA_LIBS})

add_executable(example_wirelessHandle examples/example_wirelessHandle.cpp)
target_link_libraries(example_wirelessHandle ${EXTRA_LIBS})

# one pc multi process
add_executable(lcm_server_high examples/lcm_server_high.cpp)
target_link_libraries(lcm_server_high ${EXTRA_LIBS})

add_executable(lcm_server_low examples/lcm_server_low.cpp)
target_link_libraries(lcm_server_low ${EXTRA_LIBS})

# multi pc
add_executable(udp_send_test examples/multi_pc_udp_send.cpp)
target_link_libraries(udp_send_test ${EXTRA_LIBS})

add_executable(udp_recv_test examples/multi_pc_udp_recv.cpp)
target_link_libraries(udp_recv_test ${EXTRA_LIBS})
add_executable(function_test examples/function.cpp)
target_link_libraries(function_test ${EXTRA_LIBS})

# lcm server
add_executable(lcm_server examples/lcm_server.cpp)
target_link_libraries(lcm_server ${EXTRA_LIBS})

# mannul
add_executable(example_sensor examples/example_read_sensor.cpp)
target_link_libraries(example_sensor ${EXTRA_LIBS})

# mannul
add_executable(udp_test examples/test.cpp)
target_link_libraries(udp_test ${EXTRA_LIBS})
