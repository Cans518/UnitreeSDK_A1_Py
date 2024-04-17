cmake_minimum_required(VERSION 2.8.3)
project(unitree_legged_sdk_python_wrapper)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3")

find_package(PythonInterp 3.6 REQUIRED PythonLibs 3.6 REQUIRED)
execute_process(COMMAND
  "${PYTHON_EXECUTABLE}" -c
  "from distutils.sysconfig import get_python_lib; print(get_python_lib())"
  OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
  OUTPUT_STRIP_TRAILING_WHITESPACE)

include_directories(../include)
link_directories(../lib)
file(GLOB_RECURSE sources "cpp/*.cpp")

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

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib/python)

add_subdirectory(third-party/pybind11)

pybind11_add_module(robot_interface python_interface.cpp)
target_link_libraries(robot_interface ${EXTRA_LIBS})

install(TARGETS robot_interface LIBRARY DESTINATION ${PYTHON_SITE_PACKAGES})
install(FILES ../lib/${LIBRARY_FILE} DESTINATION /usr/local/lib)
install(CODE "execute_process(COMMAND ldconfig)")
