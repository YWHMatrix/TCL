//打开设备,初始化播放器
#include "dev_init.h"


 int lcd_fd,ts_fd;
 int *lcd_ptr;

int dev_init()
{
	lcd_fd = open("/dev/fb0", O_RDWR);

	if (lcd_fd == -1) {
		printf("open lcd device failed!\n");
		return -1;
	}
    ts_fd = open("/dev/input/event0", O_RDWR);

	if (ts_fd == -1) {
		printf("open ts device failed!\n");
		return -1;
	}

	//为lcd屏幕建立内存映射关系
	lcd_ptr = (int*)mmap(NULL, 800*480*4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);

	if (lcd_ptr ==  MAP_FAILED) {
		printf("mmap failed!\n");
		return -2;
	}
	
	ts_fd = open("/dev/input/event0", O_RDONLY);

	if (ts_fd == -1) {
		printf("open ts device failed!\n");
		return -3;
	}
		return 0;
}