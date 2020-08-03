//关闭设备
#include "dev_uninit.h"

int dev_uninit()
{
	munmap(lcd_ptr, 800*480*4);//解除内存映射
	close(lcd_fd);
	close(ts_fd);
}