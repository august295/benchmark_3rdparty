set(BUILD_EXAMPLES OFF)
set(WITH_GFLAGS OFF)
set(WITH_GTEST OFF)
set(BUILD_TESTING OFF)
add_subdirectory(${ROOT_DIR}/3rdparty/glog)

set_property(TARGET glog PROPERTY FOLDER glog)
set_property(TARGET glog_internal PROPERTY FOLDER glog)
