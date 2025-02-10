cmake_minimum_required(VERSION 3.12)
set(PREFIX_FOLDER "3rdparty")

####################################################################################################
# googletest
####################################################################################################
add_subdirectory(${ROOT_DIR}/3rdparty/googletest)

set_property(TARGET "gtest" PROPERTY FOLDER "${PREFIX_FOLDER}/googletest")
set_property(TARGET "gtest_main" PROPERTY FOLDER "${PREFIX_FOLDER}/googletest")
set_property(TARGET "gmock" PROPERTY FOLDER "${PREFIX_FOLDER}/googletest")
set_property(TARGET "gmock_main" PROPERTY FOLDER "${PREFIX_FOLDER}/googletest")


####################################################################################################
# benchmark
####################################################################################################
set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(${ROOT_DIR}/3rdparty/benchmark)

set_property(TARGET "benchmark" PROPERTY FOLDER "${PREFIX_FOLDER}/benchmark")
set_property(TARGET "benchmark_main" PROPERTY FOLDER "${PREFIX_FOLDER}/benchmark")

####################################################################################################
# tinyxml2
####################################################################################################
set(tinyxml2_BUILD_TESTING OFF)
set(tinyxml2_INSTALL_PKGCONFIG OFF)
add_subdirectory(${ROOT_DIR}/3rdparty/tinyxml2)

set_property(TARGET "tinyxml2" PROPERTY FOLDER "${PREFIX_FOLDER}")

####################################################################################################
# glog
####################################################################################################
set(BUILD_EXAMPLES OFF)
set(WITH_GFLAGS OFF)
set(WITH_GTEST OFF)
set(BUILD_TESTING OFF)
add_subdirectory(${ROOT_DIR}/3rdparty/glog)

set_property(TARGET "glog" PROPERTY FOLDER "${PREFIX_FOLDER}/glog")
set_property(TARGET "glog_internal" PROPERTY FOLDER "${PREFIX_FOLDER}/glog")
