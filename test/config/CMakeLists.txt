# test for config
add_executable(test Config_test.cpp ${PROJECT_ROOT}/Main/Config.cpp ${PROJECT_ROOT}/Main/utils/Log.cpp)
target_include_directories(test PUBLIC ${PROJECT_ROOT}/Main)

set(CMAKE_PREFIX_PATH D:/cdk/qt/5.15.2/mingw81_64)
find_package(Qt5 REQUIRED Core Gui Widgets)

target_link_libraries(test Qt5::Core Qt5::Gui Qt5::Widgets)

add_custom_command(
    TARGET test
    POST_BUILD
    COMMAND
    ${CMAKE_COMMAND} -E
      rm $<TARGET_FILE_DIR:test>/config.json
    COMMAND
      ${CMAKE_PREFIX_PATH}/bin/windeployqt $<TARGET_FILE_DIR:test>/test.exe
)