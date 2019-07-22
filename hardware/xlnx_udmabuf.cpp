#include "xlnx_udmabuf.h"





int xlnx_udmabuf::open_device(int dev_id)
{
	int ret;
	unsigned char buff[1024];
	dev_id_ = dev_id;
	 
	sprintf(buff, "/dev/udmabuf%d", dev_id);
	fd = open(buff, O_RDWR);
	if (fd < 0) {
		printf("Failed to open udmabuf: %d\n", dev_id_);
		return -1;
	}
	
	ret = get_phys_addr(&phys_addr_);
	if (ret < 0) {
		printf("Failed to get phys_addr udmabuf: %d\n", dev_id_);
		return -1;
	}
	
	ret = get_size(&size_);
	if (ret < 0) {
		printf("Failed to get size udmabuf: %d\n", dev_id_);
		return -1;
	}
	alloc_size_ = 0;
	
	virt_addr_ = mmap(NULL, size_, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (virt_addr_ == MAP_FAILED) {
		printf("Failed to mmap udmabuf: %d\n", dev_id_);
		return -1;
	}
	
	return 0;
}

int xlnx_udmabuf::close_device()
{
	munmap(virt_addr_, size_);
	close(fd);
	return 0;
}

void *xlnx_udmabuf::alloc_memory(unsigned int size, unsigned long *phy)
{
	unsigned char *base = (unsigned char *)virt_addr_;
	if ((alloc_size_ + size) >= size_)
		return NULL;
	
	unsigned char *ptr = &base[alloc_size_];
	*phy = phys_addr_ + alloc_size_;
	alloc_size_ += size;
	return (void *)ptr;
}

void xlnx_udmabuf::free_all_memory()
{
	alloc_size_ = 0;
}	
	

int xlnx_udmabuf::get_phys_addr(unsigned long *phys_addr)
{
	unsigned char buff[1024];
	unsigned char attr[1024];
	
	sprintf(buff, "/sys/class/udmabuf/udmabuf%d/phys_addr", dev_id_);
	int fd = open(buff, O_RDONLY);
	if (fd < 0) {
		printf("Failed to open: %s\n", buff);
		return -1;
	}
	
	read(fd, attr, 1024);
	sscanf(attr, "%x", phys_addr);
	close(fd);
	
	return 0;
}

int xlnx_udmabuf::get_size(unsigned int *size)
{
	unsigned char buff[1024];
	unsigned char attr[1024];
	
	sprintf(buff, "/sys/class/udmabuf/udmabuf%d/size", dev_id_);
	int fd = open(buff, O_RDONLY);
	if (fd < 0) {
		printf("Failed to open: %s\n", buff);
		return -1;
	}
	
	read(fd, attr, 1024);
	sscanf(attr, "%x", size);
	close(fd);
	
	return 0;
}























