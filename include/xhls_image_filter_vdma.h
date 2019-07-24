#ifndef __XHLS_IMAGE_FILTER_VDMA_H
#define __XHLS_IMAGE_FILTER_VDMA_H


#include "xlnx_vdma_loop.h"


class xhls_image_filter_regctl;


class xhls_image_filter_vdma : public xlnx_vdma_loop
{
public:
	xhls_image_filter_vdma(int width, int height, int bpp);
	
protected:	
	virtual int create_map_parts();
	virtual int free_map_parts();	
	
	virtual int create_hls_image_filter_port();
	virtual int free_hls_image_filter_port();
protected:
	xhls_image_filter_regctl *ximage_filter;
};






















#endif







