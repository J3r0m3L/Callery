file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_library(SqlQueryBuilder ${sources})
target_include_directories(SqlQueryBuilder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
