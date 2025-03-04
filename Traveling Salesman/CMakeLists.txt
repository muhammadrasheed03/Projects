cmake_minimum_required( VERSION 3.20 )
project( tsp VERSION 1.0 )

message( "Using sources: travelingSalesman.cpp" )
add_executable( tsp )
target_sources( tsp PRIVATE travelingSalesman.cpp )

target_compile_features( tsp PRIVATE cxx_std_20 )
install( TARGETS tsp DESTINATION . )
