# - Find YUV
# Find the native YUV includes and library
#
#  YUV_INCLUDE_DIRS - where to find YUV.h, etc.
#  YUV_LIBRARIES   - List of libraries when using YUV.
#  YUV_FOUND       - True if YUV found.

# 判断是否已经包含yuv
if (YUV_INCLUDE_DIR)
  set(YUV_FIND_QUIETLY TRUE)
endif ()

# 查找头文件位置
# PATH_SUFFIXES 路径后缀，正常安装的yuv位于系统路径/yuv/文件夹下
find_path(YUV_INCLUDE_DIR
  NAMES libyuv.h
  # 可以通过以下命令来手动制定查找路径
  PATHS /opt/local/include /usr/local/include /usr/include $ENV{YUV_ROOT}/include 
  #PATH_SUFFIXES yuv
  DOC "YUV include directories"
)

# 查找库文件位置
find_library(YUV_LIBRARY
  NAMES yuv
  PATHS /usr/lib $ENV{YUV_ROOT}/lib 
  DOC "YUV library"
)

# 同时找到头文件位置和库文件位置时给相关变量赋值
if (YUV_INCLUDE_DIR AND YUV_LIBRARY)
  message(STATUS "Found YUV (include: ${YUV_INCLUDE_DIR}, library: ${YUV_LIBRARY})")
  
  set(YUV_FOUND TRUE)
  set(YUV_LIBRARIES ${YUV_LIBRARY})
  set(YUV_INCLUDE_DIRS ${YUV_INCLUDE_DIR})
else ()
  set(YUV_FOUND FALSE)
  message(WARNING "YUV not found")
endif ()

# 打印一些错误信息
if (YUV_FOUND)
  if (NOT YUV_FIND_QUIETLY)
    message(STATUS "Found YUV: ${YUV_LIBRARIES}")
  endif ()
else ()
  if (YUV_FIND_REQUIRED)
    message(STATUS "Looked for YUV libraries named ${YUVS_NAMES}.")
    message(FATAL_ERROR "Could NOT find YUV library")
  endif ()
endif ()

# 这个选项不是很懂，貌似是给cmake gui用的
mark_as_advanced(
  YUV_LIBRARIES
  YUV_INCLUDE_DIRS
)