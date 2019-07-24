
if (POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})


find_package(OpenCV REQUIRED)
if(NOT OpenCV_FOUND)
	message("Failed to find OpenCV!!!")
else()
	include_directories(${OpenCV_INCLUDE_DIRS})
#	SET(LIBS ${LIBS} ${OpenCV_LIBS})
endif()



#SET(LIBS ${LIBS} zynq_hardware)

ADD_EXECUTABLE(vdma-loop-demo vdma_loop_demo.cpp)
TARGET_LINK_LIBRARIES(vdma-loop-demo 
	${OpenCV_LIBS}
	xhls)
	
	
#INSTALL(TARGETS stereo_demo DESTINATION bin)

