# - Find RPCLIB
# Find the native RPCLIB includes and library
#
#  RPCLIB_INCLUDE_DIRS - where to find RPCLIB.h, etc.
#  RPCLIB_LIBRARIES   - List of libraries when using RPCLIB.
#  RPCLIB_FOUND       - True if RPCLIB found.

# 判断是否已经包含yuv
if (RPCLIB_INCLUDE_DIR)
  set(RPCLIB_FIND_QUIETLY TRUE)
endif ()

# 查找头文件位置
# PATH_SUFFIXES 路径后缀，正常安装的yuv位于系统路径/yuv/文件夹下
find_path(RPCLIB_INCLUDE_DIR
  NAMES rpc/rpc_error.h
  # 可以通过以下命令来手动制定查找路径
  PATHS /opt/local/include /usr/local/include /usr/include $ENV{RPCLIB_ROOT}/include 
  #PATH_SUFFIXES yuv
  DOC "RPCLIB include directories"
)

# 查找库文件位置
find_library(RPCLIB_LIBRARY
  NAMES rpc
  PATHS /usr/lib $ENV{RPCLIB_ROOT}/lib 
  DOC "RPCLIB library"
)

# 同时找到头文件位置和库文件位置时给相关变量赋值
if (RPCLIB_INCLUDE_DIR AND RPCLIB_LIBRARY)
  message(STATUS "Found RPCLIB (include: ${RPCLIB_INCLUDE_DIR}, library: ${RPCLIB_LIBRARY})")
  
  set(RPCLIB_FOUND TRUE)
  set(RPCLIB_LIBRARIES ${RPCLIB_LIBRARY})
  set(RPCLIB_INCLUDE_DIRS ${RPCLIB_INCLUDE_DIR})
else ()
  set(RPCLIB_FOUND FALSE)
  message(WARNING "RPCLIB not found")
endif ()

# 打印一些错误信息
if (RPCLIB_FOUND)
  if (NOT RPCLIB_FIND_QUIETLY)
    message(STATUS "Found RPCLIB: ${RPCLIB_LIBRARIES}")
  endif ()
else ()
  if (RPCLIB_FIND_REQUIRED)
    message(STATUS "Looked for RPCLIB libraries named ${RPCLIBS_NAMES}.")
    message(FATAL_ERROR "Could NOT find RPCLIB library")
  endif ()
endif ()

# 这个选项不是很懂，貌似是给cmake gui用的
mark_as_advanced(
  RPCLIB_LIBRARIES
  RPCLIB_INCLUDE_DIRS
)