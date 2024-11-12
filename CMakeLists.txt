cmake_minimum_required(VERSION 3.20)
project(httpmon VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(SOURCE_DIR "src")
set(INCLUDE_DIR "include")

set(HEADERS
  ${INCLUDE_DIR}/request.hpp
  ${INCLUDE_DIR}/response.hpp
  ${INCLUDE_DIR}/response_factory.hpp
  ${INCLUDE_DIR}/http.hpp
  ${INCLUDE_DIR}/socket.hpp
  ${INCLUDE_DIR}/constants.hpp
)
set(SOURCES
  ${SOURCE_DIR}/main.cpp
  ${SOURCE_DIR}/http.cpp
  ${SOURCE_DIR}/socket.cpp
  ${SOURCE_DIR}/request.cpp
  ${SOURCE_DIR}/response.cpp
  ${SOURCE_DIR}/response_factory.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(httpmon PRIVATE include)
target_compile_options(httpmon PRIVATE -Wall -Wextra -Wpedantic)

