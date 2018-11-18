cmake_minimum_required(VERSION 3.0)

include(Common)

project("p7client")

set(PROJECT_LIB_NAME p7client)


file(GLOB_RECURSE all_headers ${CMAKE_CURRENT_LIST_DIR}/Headers/*.h*)
file(GLOB_RECURSE all_headers ${CMAKE_CURRENT_LIST_DIR}/Sources/*.h*)
file(GLOB_RECURSE all_headers ${CMAKE_CURRENT_LIST_DIR}/Shared/*.h*)
file(GLOB_RECURSE all_sources ${CMAKE_CURRENT_LIST_DIR}/Sources/*.c*)
file(GLOB_RECURSE all_resources ${CMAKE_CURRENT_LIST_DIR}/Sources/*.rc)

add_library(${PROJECT_LIB_NAME} STATIC ${all_headers};${all_sources};${all_resources})

initialize_library_target_defaults(${PROJECT_LIB_NAME} "32bit")

source_groups_from_dir_list("Header Files" FILES ${CMAKE_CURRENT_LIST_DIR} *.h*)
source_groups_from_dir_list("Source Files" FILES ${CMAKE_CURRENT_LIST_DIR} *.c*)
source_groups_from_dir_list("Resource Files" FILES ${CMAKE_CURRENT_LIST_DIR} *.rc)

if(WIN32)
target_include_directories(${PROJECT_LIB_NAME}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Shared
    ${CMAKE_CURRENT_LIST_DIR}/Shared/Platforms/Windows_x86
    ${CMAKE_CURRENT_LIST_DIR}/Headers
)
elseif(UNIX)
target_include_directories(${PROJECT_LIB_NAME}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Shared
    ${CMAKE_CURRENT_LIST_DIR}/Shared/Platforms/Linux_x86
    ${CMAKE_CURRENT_LIST_DIR}/Headers
)
endif()

if(GCC)
  add_target_compile_properties(${PROJECT_LIB_NAME} *
    -pthread
  )

  add_target_link_properties(${PROJECT_LIB_NAME} *
    -pthread
    -ldl -lrt
  )
endif()

if(WIN32)
  #find_package(WindowsSDK REQUIRED)
  #get_windowssdk_include_dirs(${WINDOWSSDK_LATEST_DIR} WINDOWSSDK_INCLUDE_DIRS)
  #get_windowssdk_library_dirs(${WINDOWSSDK_LATEST_DIR} WINDOWSSDK_LIBRARY_DIRS)
  #message(STATUS "(*) Found `WindowsSDK`: ${WINDOWSSDK_FOUND} Latest Dir: \"${WINDOWSSDK_LATEST_DIR}\" Latest Name: ${WINDOWSSDK_LATEST_NAME} "
  #  "Includes: [${WINDOWSSDK_INCLUDE_DIRS}] Library Dirs: [${WINDOWSSDK_LIBRARY_DIRS}]")

  #link_directories(${WINDOWSSDK_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_LIB_NAME} wsock32 ws2_32)
endif()
