#include "xlnx_vdma_loop.h"


xlnx_vdma_loop::xlnx_vdma_loop(int width, int height, int bpp)
{
	this->width = width;
	this->height = height;
	this->bpp = bpp;
}


int xlnx_vdma_loop::open_device(const char *dev_name)
{
	int ret;
	uio_ = uio_find_by_uio_name (dev_name);
	if (!uio) {
		printf("Failed to find uio: %s!\n", dev_name);
		return -1;
	}
	ret = uio_open(uio_);	
	if (ret < 0) {
		printf("Failed to open uio: %s!\n", dev_name);
		return -1;
	}
	
	create_map_part();
	
	return 0;
}


int xlnx_vdma_loop::open_device(u32 base_addr)
{
	int ret;
	uio_ = uio_find_by_base_addr (base_addr);
	if (!uio) {
		printf("Failed to find uio: 0x%x!\n", base_addr);
		return -1;
	}
	ret = uio_open(uio_);	
	if (ret < 0) {
		printf("Failed to open uio: 0x%x!\n", base_addr);
		return -1;
	}
	
	create_map_parts();
	
	return 0;
}

int xlnx_vdma_loop::close_device()
{
	delete_map_parts();
	uio_close (uio_);
	return 0;
}

int xlnx_vdma_loop::compute(u32 in_ddr, u32 out_ddr, int timeout)
{
	int ret;
	struct timeval tv;
	memset((void *)&tv, 0, sizeof(tv));
	tv.tv_sec = timeout;
	tv.tv_usec = 0;
	
	ret = xvmda->set_soft_reset();
	if (ret < 0) {
		printf("xvmda->set_soft_reset() error!\n");
		return -1;
	}

	ret = uio_enable_irq(uio_);
	if (ret < 0) {
		printf("uio_enable_irq(uio_) error!\n");
		return -1;
	}
	
	ret = xvmda->set_vdma_channel_sample(in_ddr, width, height, bpp, 0);
	if (ret < 0) {
		printf("xvmda->set_vdma_channel_sample() error!\n");
		return -1;
	}
	
	ret = xvmda->set_vdma_channel_sample(out_ddr, width, height, bpp, 1);
	if (ret < 0) {
		printf("xvmda->set_vdma_channel_sample() error!\n");
		return -1;
	}
	
	ret = uio_irqwait_timeout(uio_, &tv);
	if (ret < 0) {
		printf("uio_irqwait_timeout(uio_, &tv) error!\n");
		return -1;
	}
	
	return 0;
}

int xlnx_vdma_loop::create_map_parts()
{
	int ret;
	
	ret = create_vdma_part();
	if (ret < 0)
		return -1;
	return 0;
}

int xlnx_vdma_loop::delete_map_parts()
{
	delete_vdma_part();
	return 0;
}

int xlnx_vdma_loop::create_vdma_part()
{
	xvmda = new xlnx_vdma_regctl(uio_, 0);
	return 0;
}

int xlnx_vdma_loop::delete_vdma_part()
{
	delete xvmda;
	return 0;
}






