SET(APP_NAME live2d)

# Set directory paths.
set(CORE_PATH ${PROJECT_ROOT}/Core)
set(FRAMEWORK_PATH ${PROJECT_ROOT}/Framework)
set(THIRD_PARTY_PATH ${PROJECT_ROOT}/thirdParty)
set(STB_PATH ${THIRD_PARTY_PATH}/stb)
set(GLEW_PATH ${THIRD_PARTY_PATH}/glew)
set(GLFW_PATH ${THIRD_PARTY_PATH}/glfw)
set(QT_INCLUDE_PATH ${THIRD_PARTY_PATH}/qt)
set(RES_PATH ${PROJECT_ROOT}/Resources)

# Configure for Linux / Windows
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  # set qt installation path
  set(CMAKE_PREFIX_PATH /usr/lib)
  # select cubism framework platform support
  set(CSM_TARGET CSM_TARGET_LINUX_GL)
  # select cubism core platform support
  set(CORE_LIB_NAME libLive2DCubismCore.so)
  # find qt libs
  find_package(Qt5 REQUIRED Core Gui Widgets X11Extras)
  # set launch file
  set(LAUNCH_SH ${PROJECT_ROOT}/utils/launch.sh)
else(CMAKE_SYSTEM_NAME MATCHES "Windows")
  # set qt installation path
  set(CMAKE_PREFIX_PATH D:/cdk/qt/5.15.2/mingw81_64)
  # select cubism framework platform support
  set(CSM_TARGET CSM_TARGET_WIN_GL)
  # select cubism core platform support
  set(CORE_LIB_NAME Live2DCubismCore.dll)
  # find qt libs
  find_package(Qt5 REQUIRED Core Gui Widgets)
endif()

# Surpress GLEW and GLFW process.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_UTILS OFF CACHE BOOL "" FORCE)

# Specify version of compiler.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---Configure OpenGL---
# Add GLEW ,GLFW.
add_subdirectory(${GLEW_PATH}/build/cmake ${CMAKE_BINARY_DIR}/glew_s)
add_subdirectory(${GLFW_PATH} ${CMAKE_BINARY_DIR}/glfw)

# ---Configure Framework---
# Specify Cubism Framework rendering.
set(FRAMEWORK_SOURCE OpenGL)
# Add Cubism Native Framework.
add_subdirectory(${FRAMEWORK_PATH} ${CMAKE_BINARY_DIR}/Framework)
# Add rendering definition to framework.
target_compile_definitions(Framework PUBLIC ${CSM_TARGET})
# Add include path of GLEW to framework.
target_include_directories(Framework PUBLIC ${GLEW_PATH}/include)
# If current compiler is mingw, add some options
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
  # extra compile options for mingw on Windows
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(Framework PRIVATE -fpermissive -Wconversion-null)
  endif()  
endif()
# Link libraries to framework.
add_library(Live2DCubismCore STATIC IMPORTED)

# ---CubismCoreLib---
# Import CubismCoreLib
set_target_properties(Live2DCubismCore
  PROPERTIES
    IMPORTED_LOCATION
      ${CORE_PATH}/dll/${CORE_LIB_NAME}
    INTERFACE_INCLUDE_DIRECTORIES
      ${CORE_PATH}/include
)
target_compile_definitions(Live2DCubismCore
  INTERFACE
  __linux__# Windows 平台上使用 mingw 也需要使用该宏，应该是没有做 mingw 的适配
  ${CSM_TARGET}
)

target_link_libraries(Framework Live2DCubismCore glew_s)

# Find opengl libraries.
find_package(OpenGL REQUIRED)

# Automatically generate meta object codes
set(CMAKE_AUTOMOC ON) 
# Make executable app.
add_executable(${APP_NAME} 
  main.cpp
  Config.cpp
  AppDelegate.cpp
)

if(${CMAKE_BUILD_TYPE} MATCHES "Release")
  set_target_properties(${APP_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
  )
else()
  set_target_properties(${APP_NAME} PROPERTIES
    WIN32_EXECUTABLE OFF
  )
  target_compile_definitions(${APP_NAME} PRIVATE APP_MODE_DEBUG)
endif()

# Add source files.
add_subdirectory(live2d)
add_subdirectory(model)
add_subdirectory(utils)
add_subdirectory(widgets)

# Link libraries to app.
target_link_libraries(${APP_NAME}
  Framework
  glfw
  ${OPENGL_LIBRARIES}
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
)
# Add X11 support for Linux
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  target_link_libraries(${APP_NAME} 
    Qt5::X11Extras
  )
endif()


# Specify include directories.
target_include_directories(${APP_NAME} PRIVATE 
  ${STB_PATH}
  ${QT_INCLUDE_PATH}/include
  live2d
   .
)

# Post build commands
add_custom_command(
  TARGET ${APP_NAME}
  POST_BUILD
  # refresh Resources directory
  COMMAND
    ${CMAKE_COMMAND} -E
      rm -rf $<TARGET_FILE_DIR:${APP_NAME}>/Resources
  COMMAND
    ${CMAKE_COMMAND} -E
      copy_directory ${RES_PATH} $<TARGET_FILE_DIR:${APP_NAME}>/Resources
  # move dynamic link lib of cubism core to runtime dir
  COMMAND
    ${CMAKE_COMMAND} -E
      copy ${CORE_PATH}/dll/${CORE_LIB_NAME} $<TARGET_FILE_DIR:${APP_NAME}>
  # [ ] test for default json
  # COMMAND
  #   ${CMAKE_COMMAND} -E
  #     rm -f $<TARGET_FILE_DIR:${APP_NAME}>/config.json
)

# Copy launch script to binary directory
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
  file(COPY ${LAUNCH_SH} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
# Move necessary qt dynamic link libs to runtime dir 
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
  add_custom_command(
        TARGET ${APP_NAME}
        POST_BUILD
        COMMAND
          ${CMAKE_PREFIX_PATH}/bin/windeployqt.exe $<TARGET_FILE_DIR:${APP_NAME}>/${APP_NAME}.exe
  )
endif()
