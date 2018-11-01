cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  ${CMAKE_MODULE_PATH}
  )

set(CMAKE_PREFIX_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_PREFIX_PATH}  
  )
  
add_executable(GSP
  src/application.cpp
  src/application.hpp
  src/main.cpp
  src/window.cpp
  src/window.hpp
  )

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

target_include_directories(GSP
  PUBLIC ${GLM_INCLUDE_DIR}
  PUBLIC ${SDL2_INCLUDE_DIR}
  PUBLIC ${GLEW_INCLUDE_DIR}
  )
  
target_link_libraries(GSP
  PUBLIC ${OPENGL_LIBRARY}
  PUBLIC ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY}
  PUBLIC ${GLEW_LIBRARY}
  PUBLIC ${GLM_LIBRARY}
  )