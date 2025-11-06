cmake_minimum_required(VERSION 3.5)
project(abb_librws)

add_compile_options(-std=c++11)

# ===========================
# Try to detect ROS/catkin
# ===========================
find_package(catkin QUIET COMPONENTS cmake_modules)

if(catkin_FOUND)
  message(STATUS "Building abb_librws with ROS/catkin support")
else()
  message(STATUS "Building abb_librws in standalone mode (no ROS)")
endif()

# ===========================
# POCO dependency
# ===========================
find_package(Poco 1.9.2 REQUIRED COMPONENTS Net Util Foundation XML)

# ===========================
# Source files
# ===========================
set(SRC_FILES
    src/rws_client.cpp
    src/rws_common.cpp
    src/rws_interface.cpp
    src/rws_poco_client.cpp
    src/rws_rapid.cpp
    src/rws_state_machine_interface.cpp)

# ===========================
# Include directories
# ===========================
include_directories(
    include
    ${Poco_INCLUDE_DIRS}
)

if(catkin_FOUND)
  include_directories(${catkin_INCLUDE_DIRS})
endif()

# ===========================
# Library definition
# ===========================
add_library(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
    ${Poco_LIBRARIES}
    PocoNet
    PocoUtil
    PocoFoundation
)

if(catkin_FOUND)
  target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})
endif()

# ===========================
# Package export
# ===========================
if(catkin_FOUND)
  catkin_package(
    INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
    DEPENDS Poco
  )
endif()

#############
## Install ##
#############
install(
  DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_export.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

install(
  DIRECTORY cmake/modules/third_party/
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(CMakePackageConfigHelpers)

# Create the ${PROJECT_NAME}Config.cmake.
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
  "${PROJECT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}Config.cmake" @ONLY
)

# Create the ${PROJECT_NAME}ConfigVersion.cmake.
write_basic_package_version_file(
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES
    "${PROJECT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}Config.cmake"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/package.xml"
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}
)

# Export targets.
set(export_targets ${export_targets};${PROJECT_NAME})
export(
  EXPORT export_${PROJECT_NAME}
  FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
  NAMESPACE ${PROJECT_NAME}::
)

install(
  EXPORT export_${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
)
