#ifndef __XLNX_VDMA_LOOP_H
#define __XLNX_VDMA_LOOP_H

#include "xlnx_vdma_regctl.h"



class xlnx_vdma_loop
{
public:
	xlnx_vdma_loop(int width, int height, int bpp);
	virtual int open_device(const char *dev_name);
	virtual int open_device(u32 base_addr);
	virtual int close_device();
	
	virtual int compute(u32 in_ddr, u32 out_ddr, int timeout);

protected:	
	virtual int create_map_parts();
	virtual int free_map_parts();
	
	virtual int create_vdma_part();
	virtual int free_vdma_part();

protected:	
	struct uio_info_t *uio_;
	int width;
	int height;
	int bpp;

	xlnx_vdma_regctl *xvmda;
	
	
	
};













#endif



