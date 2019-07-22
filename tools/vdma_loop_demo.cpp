#include "xlnx_vdma_loop.h"
#include "xlnx_udmabuf.h"







int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("usage: %s src.bmp dst.bmp\n", argv[0]);
		return -1;
	}	
	
	char *src_name = strdup(argv[1]);
	char *dst_name = strdup(argv[2]);
	
	Mat src_img = imread(src_name, 0);
	if (src_img.empty())
		return -1;
	int width = src_img.size().width;
	int height = src_img.size().height;
	
	xlnx_vdma_loop(width, height, 1);
	
}













