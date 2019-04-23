cmake_minimum_required(VERSION 2.8.12)
project(yaron)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE SOURCE "source/*.cpp")

include_directories(
  include/
  )

# copy resource files
file(COPY "resources" DESTINATION ".")

# compile applications
file(GLOB apps "apps/*.cpp")
foreach(app ${apps})
  string(REGEX REPLACE "[^.]*/([^.]+)\\.[^/]*" "\\1" APP_NAME ${app})
  #get_filename_component(APP_NAME ${app} NAME_WE)

  add_executable(${APP_NAME} ${SOURCE} ${app})
  target_link_libraries(${APP_NAME} ${CONAN_LIBS})
endforeach()
