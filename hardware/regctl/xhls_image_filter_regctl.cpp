#include "xhls_image_filter_regctl.h"
#include "xhls_reg_common.h"
#include "xhls_image_filter_hw.h"





xhls_image_filter_regctl::xhls_image_filter_regctl(struct uio_info_t* info, int map)
{
	info_ = info;
	map_ = map;
}

int xhls_image_filter_regctl::set_width(u32 value)
{
	int ret;
	ret = uio_write32(info_, map_, XHLS_IMAGE_FILTER_AXILITES_ADDR_COLS_DATA, value);
	if (ret < 0)
		return -1;
	return 0;
}

int xhls_image_filter_regctl::set_height(u32 value)
{
	int ret;
	ret = uio_write32(info_, map_, XHLS_IMAGE_FILTER_AXILITES_ADDR_ROWS_DATA, value);
	if (ret < 0)
		return -1;
	return 0;
}

int xhls_image_filter_regctl::set_restart(u32 value)
{
	int ret;
	
	u32 reg = 0;
	ret = uio_read32(info_, map_, XHLS_IMAGE_FILTER_AXILITES_ADDR_AP_CTRL, &reg);
	if (ret < 0)
		return -1;
	
	if (value)
		reg |= XHLS_REG_CTRL_AUTO_RESTART;
	else
		reg &= ~XHLS_REG_CTRL_AUTO_RESTART;
	
	ret = uio_write32(info_, map_, desc_offset(chan, XILINX_DMA_REG_FRMDLY_STRIDE), width * bpp);
	if (ret < 0)
		return -1;
	
	return 0;
}

int xhls_image_filter_regctl::set_start(u32 value)
{
	int ret;
	
	u32 reg = 0;
	ret = uio_read32(info_, map_, XHLS_IMAGE_FILTER_AXILITES_ADDR_AP_CTRL, &reg);
	if (ret < 0)
		return -1;
	
	if (value)
		reg |= XHLS_REG_CTRL_START;
	else
		reg &= ~XHLS_REG_CTRL_START;
	
	ret = uio_write32(info_, map_, desc_offset(chan, XILINX_DMA_REG_FRMDLY_STRIDE), width * bpp);
	if (ret < 0)
		return -1;
	
	return 0;
}









