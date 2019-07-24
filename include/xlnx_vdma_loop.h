#ifndef __XLNX_VDMA_LOOP_H
#define __XLNX_VDMA_LOOP_H

struct uio_info_t;
class xlnx_vdma_regctl;



class xlnx_vdma_loop
{
public:
	xlnx_vdma_loop(int width, int height, int bpp);
	virtual int open_device(const char *dev_name);
	virtual int open_device(unsigned int base_addr);
	virtual int close_device();
	
	virtual int compute(unsigned int in_ddr, unsigned int out_ddr, int timeout);

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



