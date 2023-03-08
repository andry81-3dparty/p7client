cmake_minimum_required(VERSION 3.0)

include(tacklelib/Project)

project("p7client")

set(PROJECT_LIB_NAME p7client)

tkl_check_var(REQUIRED PATH   P7CLIENT_BRANCH_NAME) # ex: `5_5_0_release`

set(PROJECT_EXTERNALS_DIR "_externals")
set(P7_EXTERNAL_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/${PROJECT_EXTERNALS_DIR}/${P7CLIENT_BRANCH_NAME}")

#>>Build options **********************************************************************
option(P7_TESTS_BUILD "Build test" OFF)
option(P7_EXAMPLES_BUILD "Build examples" OFF)
#<<Build options **********************************************************************

include(CheckCXXCompilerFlag)
function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
    endif()
endfunction()

if (P7_SOURCE_DIR STREQUAL "")
  set(P7_EXTERNAL_SOURCE_DIR "${}")
endif()

file(GLOB_RECURSE all_headers ${P7_EXTERNAL_SOURCE_DIR}/Headers/*.h*)
file(GLOB_RECURSE all_headers ${P7_EXTERNAL_SOURCE_DIR}/Sources/*.h*)
file(GLOB_RECURSE all_headers ${P7_EXTERNAL_SOURCE_DIR}/Shared/*.h*)
file(GLOB_RECURSE all_sources ${P7_EXTERNAL_SOURCE_DIR}/Sources/*.c*)

if (WIN32 AND NOT MINGW)
  file(GLOB_RECURSE all_resources ${P7_EXTERNAL_SOURCE_DIR}/Sources/*.rc)
else()
  set(all_resources "")
endif()

add_library(${PROJECT_LIB_NAME} STATIC ${all_headers};${all_sources};${all_resources})

tkl_initialize_library_target_defaults(${PROJECT_LIB_NAME} "anybit")

tkl_source_groups_from_dir_list("Header Files" FILES ${P7_EXTERNAL_SOURCE_DIR} *.h*)
tkl_source_groups_from_dir_list("Source Files" FILES ${P7_EXTERNAL_SOURCE_DIR} *.c*)
tkl_source_groups_from_dir_list("Resource Files" FILES ${P7_EXTERNAL_SOURCE_DIR} *.rc)

if (MSVC)
  tkl_add_target_compile_definitions(${PROJECT_LIB_NAME} *
    PRIVATE
      _UNICODE
      UNICODE
  )
else()
  enable_cxx_compiler_flag_if_supported("-Wall")
  enable_cxx_compiler_flag_if_supported("-Wextra")
  enable_cxx_compiler_flag_if_supported("-pedantic")
  enable_cxx_compiler_flag_if_supported("-D_FILE_OFFSET_BITS=64")
  enable_cxx_compiler_flag_if_supported("-D_LARGEFILE64_SOURCE")
  enable_cxx_compiler_flag_if_supported("-fvisibility=hidden")
  enable_cxx_compiler_flag_if_supported("-Wno-variadic-macros")
  enable_cxx_compiler_flag_if_supported("-Wno-long-long")
  enable_cxx_compiler_flag_if_supported("-Wno-missing-field-initializers")
  enable_cxx_compiler_flag_if_supported("-Wno-unknown-pragmas")
  enable_cxx_compiler_flag_if_supported("-fPIC")
endif()

if (WIN32 AND NOT MINGW)
  target_include_directories(${PROJECT_LIB_NAME}
    PUBLIC
      ${P7_EXTERNAL_SOURCE_DIR}/Shared
      ${P7_EXTERNAL_SOURCE_DIR}/Shared/Platforms/Windows_x86
      ${P7_EXTERNAL_SOURCE_DIR}/Headers
  )
elseif (UNIX OR MINGW)
  target_include_directories(${PROJECT_LIB_NAME}
    PUBLIC
      ${P7_EXTERNAL_SOURCE_DIR}/Shared
      ${P7_EXTERNAL_SOURCE_DIR}/Shared/Platforms/Linux_x86
      ${P7_EXTERNAL_SOURCE_DIR}/Headers
  )
  if (MINGW)
    tkl_add_target_compile_definitions(${PROJECT_LIB_NAME} *
      PRIVATE
        MINGW
    )
  endif()
endif()

if (WIN32)
  #find_package(WindowsSDK REQUIRED)
  #get_windowssdk_include_dirs(${WINDOWSSDK_LATEST_DIR} WINDOWSSDK_INCLUDE_DIRS)
  #get_windowssdk_library_dirs(${WINDOWSSDK_LATEST_DIR} WINDOWSSDK_LIBRARY_DIRS)
  #message(STATUS "(*) Found `WindowsSDK`: ${WINDOWSSDK_FOUND} Latest Dir: \"${WINDOWSSDK_LATEST_DIR}\" Latest Name: ${WINDOWSSDK_LATEST_NAME} "
  #  "Includes: [${WINDOWSSDK_INCLUDE_DIRS}] Library Dirs: [${WINDOWSSDK_LIBRARY_DIRS}]")

  #link_directories(${WINDOWSSDK_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_LIB_NAME}
    wsock32 ws2_32
  )
elseif (MINGW)
  target_link_libraries(${PROJECT_LIB_NAME}
    ${CMAKE_DL_LIBS} pthread
  )
elseif (UNIX AND NOT APPLE)
  target_link_libraries(${PROJECT_LIB_NAME}
    ${CMAKE_DL_LIBS} rt pthread
  )
endif()
