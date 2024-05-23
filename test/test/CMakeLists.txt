set(CMAKE_BUILD_TYPE "Debug")
add_executable(test test.cpp)

target_sources(test PRIVATE
    ${PROJECT_ROOT}/Main/model/model_dir/ModelDirectory.cpp
    ${PROJECT_ROOT}/Main/utils/log/Log.cpp
    )

target_include_directories(test PRIVATE
    ${PROJECT_ROOT}/Main)