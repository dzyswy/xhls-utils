
if (POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})


find_package(OpenCV REQUIRED)
if(NOT OpenCV_FOUND)
	message("fail to find OpenCV")
else()
	include_directories(${OpenCV_INCLUDE_DIRS})
#	SET(LIBS ${LIBS} ${OpenCV_LIBS})
	message(STATUS "OpenCV library status:")
	message(STATUS "    version: ${OpenCV_VERSION}")
	message(STATUS "    include: ${OpenCV_INCLUDE_DIRS}")
	message(STATUS "    library: ${OpenCV_INSTALL_PATH}")
	message(STATUS "    libs: ${OpenCV_LIBS}")
endif()



#SET(LIBS ${LIBS} zynq_hardware)

ADD_EXECUTABLE(vdma-loop-demo vdma_loop_demo.cpp)
TARGET_LINK_LIBRARIES(vdma-loop-demo 
	${OpenCV_LIBS} 
	xhls)
	
ADD_EXECUTABLE(image-filter-vdma-demo image_filter_vdma_demo.cpp)
TARGET_LINK_LIBRARIES(image-filter-vdma-demo 
	${OpenCV_LIBS} 
	xhls)	
	
	
INSTALL(TARGETS vdma-loop-demo DESTINATION bin)
INSTALL(TARGETS image-filter-vdma-demo DESTINATION bin)

