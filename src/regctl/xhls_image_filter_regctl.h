#ifndef __XHLS_IMAGE_FILTER_REGCTL_H
#define __XHLS_IMAGE_FILTER_REGCTL_H


#include "libuio.h"
#include "xhls_reg_common.h"

class xhls_image_filter_regctl
{
public:
	xhls_image_filter_regctl(struct uio_info_t* info, int map);
	int set_width(u32 value);
	int set_height(u32 value);
	int set_restart(u32 value);
	int set_start(u32 value);
	
	
protected:
	struct uio_info_t* info_;
	int map_;
	
	
};











#endif

