cmake_minimum_required(VERSION 3.5)
project(pcl_processing)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_definitions(-DROS2_BUILD)

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(pcl_ros REQUIRED)
find_package(perception_pcl REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(om_aiv_msg REQUIRED)
find_package(visualization_msgs REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
  include
  ${rclcpp_INCLUDE_DIRS}
  ${rclcpp_action_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

link_directories(${catkin_LIBRARY_DIRS})


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

include_directories(include
  ${CMAKE_CURRENT_SOURCE_DIR}
)


set(HEADERS
  include/pcl_processing/camera_calibration.hpp
  include/pcl_processing/pcl_processing.hpp
)

add_library(camera_calibration src/camera_calibration.cpp)

add_executable(pcl_processing
  src/pcl_processing.cpp
)

ament_target_dependencies(pcl_processing
  rclcpp
  sensor_msgs
  pcl_conversions
  pcl_ros
  perception_pcl
  geometry_msgs
  om_aiv_msg
)

target_link_libraries(pcl_processing
  ${Boost_SYSTEM_LIBRARY}  # pcl_conversions requires this
  camera_calibration
)

install(TARGETS
  pcl_processing
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  config
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
