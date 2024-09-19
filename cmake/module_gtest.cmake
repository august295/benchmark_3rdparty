add_subdirectory(${ROOT_DIR}/3rdparty/googletest)

set_property(TARGET gtest PROPERTY FOLDER googletest)
set_property(TARGET gtest_main PROPERTY FOLDER googletest)
set_property(TARGET gmock PROPERTY FOLDER googletest)
set_property(TARGET gmock_main PROPERTY FOLDER googletest)
