project(GSP)

cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)
set(GLEW_VERSION 2.1)

set(CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  ${CMAKE_MODULE_PATH}
  )

set(CMAKE_PREFIX_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_PREFIX_PATH}  
  )
  
add_executable(GSP
  src/application.cpp
  src/application.hpp
  src/main.cpp
  src/geometry.hpp
  src/geometry.cpp
  src/window.cpp
  src/window.hpp
  src/scene.cpp
  src/scene.hpp
  src/renderer.cpp
  src/renderer.hpp
  src/mesh.cpp
  src/mesh.hpp
  src/tile.h
  src/tile.cpp
  src/field.h
  src/field.cpp
  src/stb_image.h
  )

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(ASSIMP REQUIRED)

target_include_directories(GSP
  PUBLIC ${GLM_INCLUDE_DIR}
  PUBLIC ${SDL2_INCLUDE_DIR}
  PUBLIC ${GLEW_INCLUDE_DIRS}
  PUBLIC ${ASSIMP_INCLUDE_DIR}
  )
  
target_link_libraries(GSP
  PUBLIC ${OPENGL_LIBRARY}
  PUBLIC ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY}
  PUBLIC GLEW::GLEW
  PUBLIC ${GLM_LIBRARY}
  PUBLIC ${ASSIMP_LIBRARY_RELEASE}
  )
