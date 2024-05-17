# test for utils/Log
add_executable(test log_test.cpp ${PROJECT_ROOT}/Main/utils/Log.cpp)
target_include_directories(test PUBLIC ${PROJECT_ROOT}/Main)