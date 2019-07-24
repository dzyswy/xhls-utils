#include "xlnx_vdma_loop.h"
#include "xlnx_udmabuf.h"
#include <opencv2/opencv.hpp>

using namespace cv;



void load_image_bgr(Mat &image, uchar *dst)
{
	int width = image.size().width; 
	for (int y = 0; y < image.size().height; y++)
	{
		const uchar *lptr = image.ptr<uchar>(y);
		memcpy(dst, lptr, width * 3);
		dst += width * 3;
	}	
}

void save_image_bgr(uchar *src, Mat &image)
{
	int width = image.size().width; 
	for (int y = 0; y < image.size().height; y++)
	{
		const uchar *lptr = image.ptr<uchar>(y);
		memcpy(lptr, src, width * 3);
		src += width * 3;
	}
}

int main(int argc, char *argv[])
{
	int ret;
	if (argc != 4)
	{
		printf("usage: %s vdma_base src.bmp dst.bmp\n", argv[0]);
		return -1;
	}	
	
	unsigned long vdma_base = strtol(argv[1], NULL, 16);
	char *src_name = strdup(argv[2]);
	char *dst_name = strdup(argv[3]);
	
	Mat src_img = imread(src_name, IMREAD_COLOR);
	if (src_img.empty())
		return -1;
	int width = src_img.size().width;
	int height = src_img.size().height;
	
	Mat dst_img;
	dst_img.create(height, width, CV_8UC3);
	
	xlnx_udmabuf xbuf;
	ret = xbuf.open_device(0);
	if (ret < 0)
		return -1;
	
	void *image_virt[2]; unsigned long image_phys[2];
	image_virt[0] = xbuf.alloc_memory(width *height * 3, &image_phys[0]);
	image_virt[1] = xbuf.alloc_memory(width *height * 3, &image_phys[1]);
	if ((!image_virt[0]) || (!image_virt[1]))
		return -1;
	
	printf("dma: 0x%lx 0x%lx\n", image_phys[0], image_phys[1]);
	 
	xlnx_vdma_loop xloop(width, height, 3);
	ret = xloop.open_device(vdma_base);
	if (ret < 0)
		return -1;
	
	load_image_bgr(src_img, (uchar *)image_virt[0]);
	
	ret = xloop.compute(image_phys[0], image_phys[1], 5);
	if (ret < 0)
		return -1;
	
	save_image_bgr(image_virt[1], dst_img);
	
	imwrite(dst_name, dst_img);
	printf("test ok!\n");
	
	return 0;
}













