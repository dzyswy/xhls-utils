#ifndef __XLNX_UDMABUF_H
#define __XLNX_UDMABUF_H


#include        <stdio.h>
#include        <fcntl.h>
#include        <string.h>
#include        <time.h>
#include        <sys/types.h>
#include        <sys/mman.h>


class xlnx_udmabuf
{
public:
	int open_device(int dev_id);
	int close_device();
	void *alloc_memory(unsigned int size, unsigned long *phy);
	void free_all_memory();
	
protected:	
	int get_phys_addr(unsigned long *phys_addr);
	int get_size(unsigned long *size);
 
protected:	
	int dev_id_;
	int fd;
	void *virt_addr_;
	unsigned long phys_addr_;
	unsigned int size_;
	unsigned int alloc_size_;
};














#endif
