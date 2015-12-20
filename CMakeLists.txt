cmake_minimum_required(VERSION 3.0.0)

#=======================
# CMake module path
#=======================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

#=======================
# Project setting
#=======================
project(MeshViewerFramework)

file(GLOB _project_SOURCE ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/command/*h ${PROJECT_SOURCE_DIR}/src/command/*cpp
        ${PROJECT_SOURCE_DIR}/src/core/*h ${PROJECT_SOURCE_DIR}/src/core/*cpp
        ${PROJECT_SOURCE_DIR}/src/io/*h ${PROJECT_SOURCE_DIR}/src/io/*cpp
        ${PROJECT_SOURCE_DIR}/src/scene/*h ${PROJECT_SOURCE_DIR}/src/scene/*cpp
        ${PROJECT_SOURCE_DIR}/src/shader/*h ${PROJECT_SOURCE_DIR}/src/shader/*cpp
        ${PROJECT_SOURCE_DIR}/src/ui/*h ${PROJECT_SOURCE_DIR}/src/ui/*cpp
        ${PROJECT_SOURCE_DIR}/src/tool/*h ${PROJECT_SOURCE_DIR}/src/tool/*cpp
        ${PROJECT_SOURCE_DIR}/src/util/*h ${PROJECT_SOURCE_DIR}/src/util/*cpp
)

#=======================
# Source group setting
#=======================
file(GLOB _command_SOURCE ${PROJECT_SOURCE_DIR}/src/command/*h ${PROJECT_SOURCE_DIR}/src/command/*cpp)
source_group("command" FILES ${_command_SOURCE})
file(GLOB _core_SOURCE ${PROJECT_SOURCE_DIR}/src/core/*h ${PROJECT_SOURCE_DIR}/src/core/*cpp)
source_group("core" FILES ${_core_SOURCE})
file(GLOB _io_SOURCE ${PROJECT_SOURCE_DIR}/src/io/*h ${PROJECT_SOURCE_DIR}/src/io/*cpp)
source_group("io" FILES ${_io_SOURCE})
file(GLOB _scene_SOURCE ${PROJECT_SOURCE_DIR}/src/scene/*h ${PROJECT_SOURCE_DIR}/src/scene/*cpp)
source_group("scene" FILES ${_scene_SOURCE})
file(GLOB _shader_SOURCE ${PROJECT_SOURCE_DIR}/src/shader/*h ${PROJECT_SOURCE_DIR}/src/shader/*cpp)
source_group("shader" FILES ${_shader_SOURCE})
file(GLOB _ui_SOURCE ${PROJECT_SOURCE_DIR}/src/ui/*h ${PROJECT_SOURCE_DIR}/src/ui/*cpp)
source_group("ui" FILES ${_ui_SOURCE})
file(GLOB _tool_SOURCE ${PROJECT_SOURCE_DIR}/src/tool/*h ${PROJECT_SOURCE_DIR}/src/tool/*cpp)
source_group("tool" FILES ${_tool_SOURCE})
file(GLOB _util_SOURCE ${PROJECT_SOURCE_DIR}/src/util/*h ${PROJECT_SOURCE_DIR}/src/util/*cpp)
source_group("util" FILES ${_util_SOURCE})


#=======================
# Setup External Libraries
#=======================
include(SetupExtLibs)

#=======================
# Visual Studio setting
#=======================
include(MSVCProperties)

#=======================
# Find Eigen
#=======================
find_package(Eigen REQUIRED)

#=======================
# Find OpenMesh
#=======================
find_package(OpenMesh REQUIRED)

#=======================
# Find OpenGL
#=======================
find_package(OpenGL REQUIRED)

#=======================
# Find Qt
#=======================
set (CMAKE_AUTOMOC ON)
set (CMAKE_PREFIX_PATH "C:/Program Files (x86)/Windows Kits/8.0/Lib/win8/um/x64")
find_package(Qt5Widgets)

#=======================
# Include setting
#=======================
include_directories(
${OPENMESH_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src
${PROJECT_SOURCE_DIR}/src/command
    ${PROJECT_SOURCE_DIR}/src/core
    ${PROJECT_SOURCE_DIR}/src/io
    ${PROJECT_SOURCE_DIR}/src/scene
    ${PROJECT_SOURCE_DIR}/src/shader
    ${PROJECT_SOURCE_DIR}/src/tool
    ${PROJECT_SOURCE_DIR}/src/ui
    ${PROJECT_SOURCE_DIR}/src/util)

#=======================
# Entry point
#=======================
add_executable( ${PROJECT_NAME} ${_project_SOURCE} )

#=======================
# Link setting
#=======================
qt5_use_modules(${PROJECT_NAME}  Widgets PrintSupport OpenGL Gui Core)
target_link_libraries(${PROJECT_NAME}  ${OPENMESH_Core_LIBRARY} ${OPENGL_LIBRARIES} ${QT_LIBRARIES})

#=======================
# Output settings.
#=======================
set(_bin_DIR ${PROJECT_SOURCE_DIR}/bin)
set_target_properties( ${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    RUNTIME_OUTPUT_DIRECTORY ${_bin_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${_bin_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${_bin_DIR}
    CLEAN_DIRECT_OUTPUT 1
)

