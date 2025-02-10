set(ProjectName "test_xml")
CreateTarget(${ProjectName} "Exe" "test")

include_directories(${ROOT_DIR}/3rdparty/googletest/googletest/include)
target_link_libraries(${ProjectName} "gtest" "gtest_main")

include_directories(${ROOT_DIR}/3rdparty/benchmark/include)
target_link_libraries(${ProjectName} "benchmark" "benchmark_main")

add_compile_definitions(PUGIXML_HEADER_ONLY)
include_directories(${ROOT_DIR}/3rdparty/pugixml/src)

include_directories(${ROOT_DIR}/3rdparty/tinyxml2)
target_link_libraries(${ProjectName} "tinyxml2")