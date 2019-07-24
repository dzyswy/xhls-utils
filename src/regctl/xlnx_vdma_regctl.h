#ifndef __XLNX_VDMA_REGCTL_H
#define __XLNX_VDMA_REGCTL_H

#include "libuio.h"
#include "xhls_reg_common.h"

class xlnx_vdma_regctl
{
public:
	xlnx_vdma_regctl(struct uio_info_t* info, int map);
	int set_soft_reset();
	int set_vdma_channel_sample(u32 ddr_base, u32 width, u32 height, u32 bpp, u32 chan);


protected:
	u32 ctrl_offset(u32 chan, u32 offset);
	u32 desc_offset(u32 chan, u32 offset);
	
protected:
	struct uio_info_t* info_;
	int map_;
	
};













#endif

