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

add_executable(pcl_filter
  src/pcl_filter.cpp
)

ament_target_dependencies(pcl_filter
  rclcpp
  sensor_msgs
  pcl_conversions
  pcl_ros
  perception_pcl
)

add_executable(pcl_processing
  src/pcl_processing.cpp
)

ament_target_dependencies(pcl_processing
  rclcpp
  sensor_msgs
  pcl_conversions
  pcl_ros
  perception_pcl
)

target_link_libraries(pcl_processing
  ${Boost_SYSTEM_LIBRARY}  # pcl_conversions requires this
)

target_link_libraries(pcl_filter
  ${Boost_SYSTEM_LIBRARY}  # pcl_conversions requires this
)

add_executable(check_box
  src/check_box.cpp
)

ament_target_dependencies(check_box
  rclcpp
  sensor_msgs
  nav_msgs
  geometry_msgs
  pcl_conversions
  pcl_ros
  perception_pcl
  om_aiv_msg
)

install(TARGETS
  pcl_filter
  check_box
  pcl_processing
  DESTINATION lib/${PROJECT_NAME}
)

# install(
#   DIRECTORY launch config map meshes param urdf
#   DESTINATION share/${PROJECT_NAME}
# )

install(DIRECTORY
  config
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
