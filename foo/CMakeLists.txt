cmake_minimum_required(VERSION 3.23)

project(FooLib)

set(CMAKE_CXX_STANDARD 20)

add_library(FooLib SHARED)
add_compile_options(-g1 -ffile-prefix-map=$PWD=. -fno-record-gcc-switches -fno-eliminate-unused-debug-types -Xlinker -Map=output.map)

add_custom_command(
    TARGET FooLib POST_BUILD
  # Use generator expressions to reference the actual target file produced by CMake.
  # This avoids hardcoding filenames (and case) which can be error-prone.
  COMMAND ${CMAKE_OBJCOPY} ARGS --only-keep-debug $<TARGET_FILE:FooLib> $<TARGET_FILE:FooLib>.debug
  COMMAND ${CMAKE_OBJCOPY} ARGS --strip-debug $<TARGET_FILE:FooLib>
  COMMAND ${CMAKE_OBJCOPY} ARGS --add-gnu-debuglink=$<TARGET_FILE:FooLib>.debug $<TARGET_FILE:FooLib>
)

target_sources(FooLib

  PUBLIC
    FILE_SET HEADERS
    FILES
      foo/lib.h

  PRIVATE
    foo/lib.cpp
)