set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(${ROOT_DIR}/3rdparty/benchmark)

set_property(TARGET benchmark PROPERTY FOLDER benchmark)
set_property(TARGET benchmark_main PROPERTY FOLDER benchmark)