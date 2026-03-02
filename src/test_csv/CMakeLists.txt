set(ProjectName "test_csv")
CreateTarget(${ProjectName} "Exe" "test")

include_directories(${ROOT_DIR}/3rdparty/googletest/googletest/include)
target_link_libraries(${ProjectName} "gtest" "gtest_main")

include_directories(${ROOT_DIR}/3rdparty/benchmark/include)
target_link_libraries(${ProjectName} "benchmark" "benchmark_main")

include_directories(${ROOT_DIR}/3rdparty/rapidcsv/src)
include_directories(${ROOT_DIR}/3rdparty/csv2/single_include)
