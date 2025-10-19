cmake_minimum_required(VERSION 3.30)
project(app)

add_compile_options(-g1 -ffile-prefix-map=$PWD=. -fno-record-gcc-switches -fno-eliminate-unused-debug-types -Xlinker -Map=output.map)

include(foo/CMakeLists.txt)

add_executable(app)
target_sources(app
    PRIVATE
    main.cpp
)

add_custom_command(
    TARGET app POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS --only-keep-debug ${CMAKE_BINARY_DIR}/app ${CMAKE_BINARY_DIR}/app.debug
    COMMAND ${CMAKE_OBJCOPY} ARGS --strip-debug ${CMAKE_BINARY_DIR}/app
    #COMMAND ${CMAKE_OBJCOPY} ARGS --add-gnu-debuglink=$<TARGET_FILE:MyTarget>.dbg $<TARGET_FILE:MyTarget>
)

target_link_libraries(app PRIVATE FooLib)