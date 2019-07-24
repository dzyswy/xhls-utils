# - Find TurboJPEG
# Find the native TurboJPEG includes and library
#
#  TurboJPEG_INCLUDE_DIRS - where to find TurboJPEG.h, etc.
#  TurboJPEG_LIBRARIES   - List of libraries when using TurboJPEG.
#  TurboJPEG_FOUND       - True if TurboJPEG found.

# 判断是否已经包含yuv
if (TurboJPEG_INCLUDE_DIR)
  set(TurboJPEG_FIND_QUIETLY TRUE)
endif ()

# 查找头文件位置
# PATH_SUFFIXES 路径后缀，正常安装的yuv位于系统路径/yuv/文件夹下
find_path(TurboJPEG_INCLUDE_DIR
  NAMES turbojpeg.h
  # 可以通过以下命令来手动制定查找路径
  PATHS /opt/local/include /usr/local/include /usr/include $ENV{TurboJPEG_ROOT}/include 
  #PATH_SUFFIXES yuv
  DOC "TurboJPEG include directories"
)

# 查找库文件位置
find_library(TurboJPEG_LIBRARY
  NAMES turbojpeg
  PATHS /usr/lib $ENV{TurboJPEG_ROOT}/lib 
  DOC "TurboJPEG library"
)

# 同时找到头文件位置和库文件位置时给相关变量赋值
if (TurboJPEG_INCLUDE_DIR AND TurboJPEG_LIBRARY)
  message(STATUS "Found TurboJPEG (include: ${TurboJPEG_INCLUDE_DIR}, library: ${TurboJPEG_LIBRARY})")
  
  set(TurboJPEG_FOUND TRUE)
  set(TurboJPEG_LIBRARIES ${TurboJPEG_LIBRARY})
  set(TurboJPEG_INCLUDE_DIRS ${TurboJPEG_INCLUDE_DIR})
else ()
  set(TurboJPEG_FOUND FALSE)
  message(WARNING "TurboJPEG not found")
endif ()

# 打印一些错误信息
if (TurboJPEG_FOUND)
  if (NOT TurboJPEG_FIND_QUIETLY)
    message(STATUS "Found TurboJPEG: ${TurboJPEG_LIBRARIES}")
  endif ()
else ()
  if (TurboJPEG_FIND_REQUIRED)
    message(STATUS "Looked for TurboJPEG libraries named ${TurboJPEGS_NAMES}.")
    message(FATAL_ERROR "Could NOT find TurboJPEG library")
  endif ()
endif ()

# 这个选项不是很懂，貌似是给cmake gui用的
mark_as_advanced(
  TurboJPEG_LIBRARIES
  TurboJPEG_INCLUDE_DIRS
)