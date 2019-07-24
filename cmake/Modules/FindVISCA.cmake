# - Find Visca
# Find the native VISCA includes and library
#
#  VISCA_INCLUDE_DIRS - where to find VISCA.h, etc.
#  VISCA_LIBRARIES   - List of libraries when using VISCA.
#  VISCA_FOUND       - True if VISCA found.

# 判断是否已经包含visca
if (VISCA_INCLUDE_DIR)
  set(VISCA_FIND_QUIETLY TRUE)
endif ()

# 查找头文件位置
# PATH_SUFFIXES 路径后缀，正常安装的visca位于系统路径/visca/文件夹下
find_path(VISCA_INCLUDE_DIR
  NAMES libvisca/libvisca.h
  # 可以通过以下命令来手动制定查找路径
  PATHS $ENV{VISCA_ROOT}/include /opt/local/include /usr/local/include /usr/include
  #PATH_SUFFIXES visca
  DOC "Visca include directories"
)

# 查找库文件位置
find_library(VISCA_LIBRARY
  NAMES visca
  PATHS /usr/lib $ENV{VISCA_ROOT}/lib
  DOC "Visca library"
)

# 同时找到头文件位置和库文件位置时给相关变量赋值
if (VISCA_INCLUDE_DIR AND VISCA_LIBRARY)
  message(STATUS "Found VISCA (include: ${VISCA_INCLUDE_DIR}, library: ${VISCA_LIBRARY})")
  
  set(VISCA_FOUND TRUE)
  set(VISCA_LIBRARIES ${VISCA_LIBRARY})
  set(VISCA_INCLUDE_DIRS ${VISCA_INCLUDE_DIR})
else ()
  set(VISCA_FOUND FALSE)
  message(WARNING "VISCA not found")
endif ()

# 打印一些错误信息
if (VISCA_FOUND)
  if (NOT VISCA_FIND_QUIETLY)
    message(STATUS "Found VISCA: ${VISCA_LIBRARIES}")
  endif ()
else ()
  if (VISCA_FIND_REQUIRED)
    message(STATUS "Looked for VISCA libraries named ${VISCAS_NAMES}.")
    message(FATAL_ERROR "Could NOT find VISCA library")
  endif ()
endif ()

# 这个选项不是很懂，貌似是给cmake gui用的
mark_as_advanced(
  VISCA_LIBRARIES
  VISCA_INCLUDE_DIRS
)