set(ProjectName "test_json")
CreateTarget(${ProjectName} "Exe" "test")

include_directories(${ROOT_DIR}/3rdparty/googletest/googletest/include)
target_link_libraries(${ProjectName} "gtest" "gtest_main")

include_directories(${ROOT_DIR}/3rdparty/benchmark/include)
target_link_libraries(${ProjectName} "benchmark" "benchmark_main")

include_directories(${ROOT_DIR}/3rdparty/json/single_include)
include_directories(${ROOT_DIR}/3rdparty/rapidjson/include)