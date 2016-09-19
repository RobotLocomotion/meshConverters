cmake_minimum_required(VERSION 3.5)
project(meshconverters LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
    "Choose the type of build; options are Debug Release RelWithDebInfo MinSizeRel"
    FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY
    STRINGS
      Debug
      Release
      RelWithDebInfo
      MinSizeRel)
endif()

find_package(OpenGL REQUIRED)
find_package(Qt4 REQUIRED)

add_executable(convert_to_obj convert_to_obj.cpp vcglib/wrap/ply/plylib.cpp)

target_include_directories(convert_to_obj PRIVATE vcglib)
target_link_libraries(convert_to_obj Qt4::QtCore Qt4::QtXml Qt4::QtXmlPatterns
  ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})

if(NOT MSVC)
  set_target_properties(convert_to_obj PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

install(TARGETS convert_to_obj DESTINATION bin)
