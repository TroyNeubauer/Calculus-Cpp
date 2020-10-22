set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/Calc.hpp")

add_library(calculuscpp lib.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(calculuscpp PUBLIC ../include)
target_compile_features(calculuscpp PUBLIC cxx_std_14)


# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})