# xhls-utils
xilinx hls ip linux driver and test
对hls ip核的行为进行抽象，屏蔽了寄存器的行为。

# 编译时依赖
uio-utils

# 运行时依赖
其本身

# 组织架构
|-src
	|-regctl
|-sample


# 编译
cmake -DCMAKE_TOOLCHAIN_FILE=../mpsoc.cmake -DCMAKE_INSTALL_PREFIX=/work/mpsoc/src/xhls-utils/libxhls-mpsoc ..

















