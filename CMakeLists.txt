
############ Setup project and cmake
# Minimum cmake requirement. We should require a quite recent
# cmake for the dependency find macros etc. to be up to date.
cmake_minimum_required( VERSION 3.12 )

############ Paths
message ("${CMAKE_BINARY_DIR}")
set (APP_BUILD_ROOT ${CMAKE_BINARY_DIR})
set (APP_BIN ${APP_BUILD_ROOT}/bin)
set (APP_LIB ${APP_BUILD_ROOT}/lib)
set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

############ Project name and version
set (APP_MAJOR_VERSION 1)
set (APP_MINOR_VERSION 0)
set (APP_PATCH_VERSION 0)
set (APP_VERSION ${APP_MAJOR_VERSION}.${APP_MINOR_VERSION}.${APP_PATCH_VERSION})
set (APP_NAME "BilibiliTool")

if(_version_allowed STREQUAL NEW)
  project (${APP_NAME} VERSION ${APP_VERSION})
else()
  project (${APP_NAME})
endif()

message ("Peoject ${APP_NAME}")

############ Configure

# Enable project folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Disable unnecessary build types
set (CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING "Configurations" FORCE)

# Include our cmake macros
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include (CMakeHelpers)

############ Build customization

############ Compiler specific setup
message (STATUS "* Compiler ${CMAKE_CXX_COMPILER_ID}")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL /Gy /GF /Ox /Ob2 /Ot /Oi /MP /arch:SSE2 /fp:fast")
  # set (CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /LTCG /INCREMENTAL:NO /OPT:REF /OPT:ICF")
  add_definitions (-DUNICODE -D_UNICODE)
  add_definitions (-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)
  add_definitions (-DNOMINMAX)
  add_definitions (-D_WIN32_WINNT=0x0A00)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set (CMAKE_CXX_STANDARD 14)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  set (CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif ()

############ Dependencies
message ("* Configuring Dependencies")

message ("** Configuring Boost")
set (APP_BOOST_LIBS system thread log random)
set (BOOST_ROOT ${BOOST_ROOT} CACHE PATH "BOOST_ROOT dependency path" FORCE)
message (STATUS "-- Using BOOST_ROOT")
message (STATUS "       " ${BOOST_ROOT})
set (Boost_USE_MULTITHREADED TRUE)
set (Boost_USE_STATIC_LIBS TRUE)
set (Boost_NO_BOOST_CMAKE ON)
find_package (Boost 1.71.0 REQUIRED COMPONENTS "${APP_BOOST_LIBS}")
if (Boost_FOUND)
	# Pretty print status
	message (STATUS "-- Include Directories")
	foreach (include_dir ${Boost_INCLUDE_DIRS})
		message (STATUS "       " ${include_dir})
	endforeach ()
	message (STATUS "-- Library Directories")
	foreach (library_dir ${Boost_LIBRARY_DIRS})
		message (STATUS "       " ${library_dir})
	endforeach ()
else ()
	message (FATAL_ERROR "Failed to find required dependency: boost")
endif ()

message ("** Configuring CURL")
set (CURL_DLL ${CURL_DLL} CACHE FILEPATH "CURL dll path" FORCE)
find_package(CURL)
if (CURL_FOUND)
  message (STATUS "CURL version: ${CURL_VERSION_STRING}")
  message (STATUS "-- Bin Path")
  message (STATUS "       " ${CURL_DLL})
  message (STATUS "-- Include Directories")
  foreach (include_dir ${CURL_INCLUDE_DIRS})
    message (STATUS "       " ${include_dir})
  endforeach ()
  message (STATUS "-- Libraries")
  foreach (library_dir ${CURL_LIBRARIES})
    message (STATUS "       " ${library_dir})
  endforeach ()
else ()
	message (FATAL_ERROR "Failed to find required dependency: CURL")
endif ()

message ("** Configuring OpenSSL")
set (OPENSSL_ROOT_DIR ${OPENSSL_ROOT_DIR} CACHE PATH "OPENSSL_ROOT_DIR dependency path" FORCE)
find_package(OpenSSL)
if (OPENSSL_FOUND)
  message (STATUS "OpenSSL version: ${OPENSSL_VERSION}")
  set (OPENSSL_BIN_DIR "${OPENSSL_ROOT_DIR}/bin" )
  message (STATUS "-- Bin Directory")
  message (STATUS "       " ${OPENSSL_BIN_DIR})
  message (STATUS "-- Include Directory")
  message (STATUS "       " ${OPENSSL_INCLUDE_DIR})
  message (STATUS "-- Libraries")
  message (STATUS "       " ${OPENSSL_CRYPTO_LIBRARY})
  message (STATUS "       " ${OPENSSL_SSL_LIBRARY})
else ()
	message (FATAL_ERROR "Failed to find required dependency: OpenSSL")
endif ()

message ("** Configuring RapidJSON")
set (RapidJSON_ROOT ${RapidJSON_ROOT} CACHE PATH "RapidJSON_ROOT dependency path" FORCE)
if (EXISTS "${RapidJSON_ROOT}/rapidjson/document.h")
  message (STATUS "-- Using RapidJSON_ROOT")
  message (STATUS "       " ${RapidJSON_ROOT})
  set (RAPIDJSON_INCLUDE_DIR ${RapidJSON_ROOT})
else ()
  message ("Cannot find ./rapidjson/document.h")
  message (FATAL_ERROR "Failed to find required dependency: RapidJSON")
endif ()

message ("** Configuring ZLIB")
set (ZLIB_ROOT ${ZLIB_ROOT} CACHE PATH "ZLIB_ROOT dependency path" FORCE)
find_package(ZLIB)
if (ZLIB_FOUND)
  message (STATUS "ZLIB version: ${ZLIB_VERSION_STRING}")
  set (ZLIB_BIN_DIR "${ZLIB_ROOT}/bin" )
  message (STATUS "-- Bin Directory")
  message (STATUS "       " ${ZLIB_BIN_DIR})
  message (STATUS "-- Include Directories")
  foreach (include_dir ${ZLIB_INCLUDE_DIRS})
    message (STATUS "       " ${include_dir})
  endforeach ()
  message (STATUS "-- Libraries")
  foreach (library_dir ${ZLIB_LIBRARIES})
    message (STATUS "       " ${library_dir})
  endforeach ()
else ()
	message (FATAL_ERROR "Failed to find required dependency: ZLIB")
endif ()

############ Add projects
message ("* Generating projects")

## 主程序
add_subdirectory (Bilibili)
