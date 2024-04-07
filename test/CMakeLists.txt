set(target ${MP2_TESTS})

file(GLOB hdrs "*.h*")
file(GLOB another_hdrs "../include/*.h*")
file(GLOB srcs "*.cpp")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty")

add_executable(${target} ${srcs} ${hdrs} ${another_hdrs} )
target_link_libraries(${target} gtest)
