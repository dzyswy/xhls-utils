# - Find UIO
# Find the native UIO includes and library
#
#  UIO_INCLUDE_DIRS - where to find UIO.h, etc.
#  UIO_LIBRARIES   - List of libraries when using UIO.
#  UIO_FOUND       - True if UIO found.

# 判断是否已经包含uio
if (UIO_INCLUDE_DIR)
  set(UIO_FIND_QUIETLY TRUE)
endif ()

message(STATUS "UIO_ROOT: $ENV{UIO_ROOT}")

# 查找头文件位置
# PATH_SUFFIXES 路径后缀，正常安装的uio位于系统路径/uio/文件夹下
find_path(UIO_INCLUDE_DIR
  NAMES libuio.h
  # 可以通过以下命令来手动制定查找路径
  PATHS /opt/local/include /usr/local/include /usr/include $ENV{UIO_ROOT}/include 
  #PATH_SUFFIXES uio
  DOC "UIO include directories"
)

# 查找库文件位置
set(uio_names ${UIO_NAMES} uio uio-static libuio libuio-static)
find_library(UIO_LIBRARY
  NAMES ${uio_names}
  PATHS /usr/lib $ENV{UIO_ROOT}/lib 
  DOC "UIO library"
)

# 同时找到头文件位置和库文件位置时给相关变量赋值
if (UIO_INCLUDE_DIR AND UIO_LIBRARY)
  message(STATUS "Found UIO (include: ${UIO_INCLUDE_DIR}, library: ${UIO_LIBRARY})")
  
  set(UIO_FOUND TRUE)
  set(UIO_LIBRARIES ${UIO_LIBRARY})
  set(UIO_INCLUDE_DIRS ${UIO_INCLUDE_DIR})
else ()
  set(UIO_FOUND FALSE)
  message(STATUS "Found UIO (include: ${UIO_INCLUDE_DIR}, library: ${UIO_LIBRARY})")
  message(WARNING "UIO not found")
endif ()

# 打印一些错误信息
if (UIO_FOUND)
  if (NOT UIO_FIND_QUIETLY)
    message(STATUS "Found UIO: ${UIO_LIBRARIES}")
  endif ()
else ()
  if (UIO_FIND_REQUIRED)
    message(STATUS "Looked for UIO libraries named ${UIOS_NAMES}.")
    message(FATAL_ERROR "Could NOT find UIO library")
  endif ()
endif ()

# 这个选项不是很懂，貌似是给cmake gui用的
mark_as_advanced(
  UIO_LIBRARIES
  UIO_INCLUDE_DIRS
)