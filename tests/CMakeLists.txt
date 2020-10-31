
set(HEADER_LIST "${CMAKE_CURRENT_SOURCE_DIR}/vendor/Catch2/single_include/catch2/catch.hpp")

add_executable(test Test.cpp DataStructures.cpp ${HEADER_LIST})

target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/Catch2/single_include)

target_link_libraries(test PRIVATE calculuscpp)
