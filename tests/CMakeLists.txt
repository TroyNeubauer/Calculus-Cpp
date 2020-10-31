
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/Calc.hpp")

add_executable(test test.cpp ${HEADER_LIST})

target_link_libraries(test PRIVATE calculuscpp)
