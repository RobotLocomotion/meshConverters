cmake_minimum_required(VERSION 2.6.0)

# set up pods
set(POD_NAME drake_mesh_converters)
include(cmake/pods.cmake)

if (NOT MSVC)
   add_definitions("-fPIC")
endif()

enable_testing()

find_package(Qt4 REQUIRED)
set(QT_USE_QTXML TRUE)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

find_package(OpenGL REQUIRED)

include_directories(vcglib)
add_executable(convert_to_obj convert_to_obj.cpp vcglib/wrap/ply/plylib.cpp)
target_link_libraries(convert_to_obj ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${QT_QTCORE_LIBRARY} ${QT_QTXMLPATTERNS_LIBRARY} ${QT_QTXML_LIBRARY})

pods_install_executables(convert_to_obj)
