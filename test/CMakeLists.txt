add_executable(test utils/log_test.cpp ../Main/utils/Log.cpp)

target_include_directories(test PUBLIC ../Main)