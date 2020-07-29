#include <sys/types.h>//打开文件
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>//内存映射

int lcd_fd, ts_fd;
int *lcd_ptr;
int dev_uninit()
{
	munmap(lcd_ptr, 800*480*4);//解除内存映射
	close(lcd_fd);
	close(ts_fd);
}