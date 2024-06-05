cmake_minimum_required(VERSION 3.14)

project(
  Tangent
  VERSION 1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES src/Tangent.cpp)

set(HEADER_FILES include/Tangent/Tangent.h)

add_library(Tangent STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(
  Tangent
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Tangent>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)

if(MSVC)
  target_compile_options(Tangent PRIVATE /W4 /WX)
  target_compile_definitions(Tangent PRIVATE TANGENT_EXPORTS)
else()
  target_compile_options(Tangent PRIVATE -Wall -Wextra -Wpedantic)
  target_compile_definitions(Tangent PRIVATE TANGENT_EXPORTS)
endif()

configure_file(include/Tangent/Version.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/Tangent/Version.h)

include(GNUInstallDirs)
install(
  TARGETS Tangent
  EXPORT TangentTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
  EXPORT TangentTargets
  FILE TangentTargets.cmake
  NAMESPACE Tangent::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Tangent)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/TangentConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/TangentConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Tangent)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/TangentConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/TangentConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Tangent)

export(
  EXPORT TangentTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/TangentTargets.cmake"
  NAMESPACE Tangent::)
export(PACKAGE Tangent)
