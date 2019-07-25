if (POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()



include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/regctl)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} XHLS_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/regctl XHLS_SRCS)

set(UIO_NAMES libuio.a)
find_package(UIO REQUIRED)
if(NOT UIO_FOUND)
	message("Failed to find UIO!!!")
else()
	include_directories(${UIO_INCLUDE_DIRS})
	message(STATUS "UIO library status:")
	message(STATUS "    include: ${UIO_INCLUDE_DIRS}")
	message(STATUS "    library: ${UIO_LIBRARIES}")
endif()


ADD_LIBRARY(xhls SHARED ${XHLS_SRCS})
TARGET_LINK_LIBRARIES(xhls 
	"-Wl,--whole-archive" 
	${UIO_LIBRARIES} 
	"-Wl,--no-whole-archive")
ADD_LIBRARY(xhls_static STATIC ${XHLS_SRCS})
set_target_properties(xhls_static PROPERTIES OUTPUT_NAME "xhls")
set_target_properties(xhls PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(xhls_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(xhls PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set_target_properties(xhls_static PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

#IF(UNIX)
#    SET_PROPERTY(TARGET xhls PROPERTY VERSION ${xhls_VERSION})
#    SET_PROPERTY(TARGET xhls PROPERTY SOVERSION ${xhls_VERSION_MAJOR})
#ENDIF(UNIX)
INSTALL(TARGETS xhls DESTINATION lib)
INSTALL(TARGETS xhls_static DESTINATION lib)
#INSTALL(DIRECTORY . DESTINATION include FILES_MATCHING PATTERN "*.h")
#INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/xhls.h DESTINATION include)
#INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/stream_func.h DESTINATION include)
#INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/record_media.h DESTINATION include)
#INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/discovery/broadcast_client.h DESTINATION include)