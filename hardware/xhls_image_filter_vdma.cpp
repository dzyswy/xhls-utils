#include "xhls_image_filter_vdma.h"


#define HLS_IMAGE_FILTER_MAP_ID		1


xhls_image_filter_vdma::xhls_image_filter_vdma(int width, int height, int bpp) 
	: xlnx_vdma_loop(widht, height, bpp)
{
	 
}



int xhls_image_filter_vdma::create_map_parts()
{
	int ret;
	ret = create_vdma_part();
	if (ret < 0)
		return -1;
	
	ret = create_hls_image_filter_port();
	if (ret < 0)
		return -1;
	
	return 0;
}

int xhls_image_filter_vdma::free_map_parts()
{
	free_hls_image_filter_port();
	free_vdma_part();
	return 0;
}

int xhls_image_filter_vdma::create_hls_image_filter_port()
{
	int ret;
	ximage_filter = new xhls_image_filter_regctl(uio_, HLS_IMAGE_FILTER_MAP_ID);
	ret = ximage_filter->set_width(width);
	if (ret < 0)
		return -1;
	ret = ximage_filter->set_height(height);
	if (ret < 0)
		return -1;
	ret = ximage_filter->set_restart(1);
	if (ret < 0)
		return -1;
	ret = ximage_filter->set_start(1);
	if (ret < 0)
		return -1;
	return 0;
}

int xhls_image_filter_vdma::free_hls_image_filter_port()
{
	delete ximage_filter;
	return 0;
}












