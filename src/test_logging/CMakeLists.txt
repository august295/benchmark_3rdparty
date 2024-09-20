set(ProjectName "test_logging")
CreateTarget(${ProjectName} "Exe" "test")

include_directories(${ROOT_DIR}/3rdparty/googletest/googletest/include)
target_link_libraries(${ProjectName} "gtest" "gtest_main")

include_directories(${ROOT_DIR}/3rdparty/benchmark/include)
target_link_libraries(${ProjectName} "benchmark" "benchmark_main")

include_directories(${ROOT_DIR}/3rdparty/spdlog/include)
include_directories(${ROOT_DIR}/3rdparty/glog/src)