cmake_minimum_required(VERSION 3.0.2)
project(time_measurer)

find_package(absl REQUIRED)

include_directories(
  "./include"
)

add_library(time_measurer SHARED
  src/time_measurer.cc
)

target_link_libraries(time_measurer
  absl::algorithm
  absl::base
  absl::debugging
  absl::flat_hash_map
  absl::memory
  absl::meta
  absl::numeric
  absl::str_format
  absl::strings
  absl::synchronization
  absl::time
  absl::utility
)

add_executable(time_measurer_test src/time_measurer_test.cc)

target_link_libraries(time_measurer_test
  ${catkin_LIBRARIES}
  time_measurer
)

# Install package.xml for catkin
install(FILES package.xml DESTINATION share/time_measurer/)

set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")
set(TIME_MEASURER_CMAKE_DIR share/time_measurer/cmake)
include(CMakePackageConfigHelpers)
configure_package_config_file(
  time_measurer-config.cmake.in
  ${PROJECT_BINARY_DIR}/cmake/time_measurer/time_measurer-config.cmake
  PATH_VARS TIME_MEASURER_CMAKE_DIR
  INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/share/time_measurer
)

install(
  FILES ${PROJECT_BINARY_DIR}/cmake/time_measurer/time_measurer-config.cmake
  DESTINATION share/time_measurer/
)

install(
  TARGETS time_measurer
  LIBRARY DESTINATION lib
)
