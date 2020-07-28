#include <stdio.h>
#include "lcdjpg.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <errno.h>

int ts_fd, lcd_fd;
int *lcd_ptr;
int get_xy(int *x, int *y)
{
	struct input_event ts;
	int x_read = 0, y_read = 1;
	while (1) {
		read(ts_fd, &ts, sizeof(ts));
		
		//绝对坐标事件(x, y)  (y (y (x, (x, (y, fin up
		if (ts.type == EV_ABS) {
			if (ts.code == ABS_X && x_read == 0) {
				*x = ts.value;
				//printf("(%d,", ts.value);
				x_read = 1;
				y_read = 0;
			}
			if (ts.code == ABS_Y && y_read == 0) {
				*y = ts.value;
				//printf(" %d)\n", ts.value);
				x_read = 0;
				y_read = 1;
			}
		}
		
		//键盘事件
		if (ts.type == EV_KEY) {
			if (ts.code == BTN_TOUCH ) {
				if (ts.value == KEY_RESERVED) {
					printf("fin up\n");
					break;
				}else if (ts.value == KEY_ESC) {
					printf("fin down\n");
				}
			}
		}
	}
	
	return 0;
}


int main(void)
{
	//1，打开触摸屏
	ts_fd = open("/dev/input/event0", O_RDWR);

	if (ts_fd == -1) {
		printf("open ts device failed!\n");
		return -1;
	}

	lcd_fd = open("/dev/fb0", O_RDWR);

	if (lcd_fd == -1) {
		printf("open lcd device failed!\n");
		return -1;
	}

	//为lcd屏幕建立内存映射关系
	lcd_ptr = (int*)mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);

	if (lcd_ptr == MAP_FAILED) {
		printf("mmap failed!\n");
		return -1;
	}

	char array[10][1024] = { "1.jpg", "2.jpg", "3.jpg","4.jpg","5.jpg","6.jpg","7.jpg" };

	lcd_draw_jpg(0, 430, array[0], NULL, 0, 0);//上一首
	lcd_draw_jpg(50, 430, array[1], NULL, 0, 0);//播放
	lcd_draw_jpg(100, 430, array[2], NULL, 0, 0);//暂停
	lcd_draw_jpg(150, 430, array[3], NULL, 0, 0);//下一首
	lcd_draw_jpg(700, 430, array[4], NULL, 0, 0);//增音量
	lcd_draw_jpg(750, 430, array[5], NULL, 0, 0);//减音量
	int value = 5;//音量
	int i = 0;
	char buf[2048];
	char av_files[10][1024] = { "1.mp3", "2.mp3", "3.mp3" };
	int x, y;
	int count = 0;
	
	while (1) {
		get_xy(&x, &y);
		printf("(%d, %d)\n", x, y);
		/*if (x >= 0 && x < 400 && y >= 0 && y < 480) {
			count--;
			//控制
			if(count == -1) {
				count = 2;
			}
			lcd_draw_jpg(0,0, array[count],NULL, 0, 0);
		}else if (x >= 400 && x < 800 && y >= 0 && y < 480) {
		//}else if (x >= 512 && x < 1024 && y >= 0 && y < 600) {
			count++;
			//控制
			if(count == 3) {
				count = 0;
			}
			lcd_draw_jpg(0,0, array[count],NULL, 0, 0);
		}
	}*/
		

		//小图标是50x50
		if (x >= 0 && x <= 50 && y >= 430 && y <= 480)//上一首
		{
			i--;
			if (i == -1)
			{
				i = 2;
			}
			sprintf(buf, "madplay %s &", av_files[i]);
			system(buf);//执行命令
		}
		else if (x > 50 && x <= 100 && y >= 430 && y <= 480)//播放
		{
			sprintf(buf, "madplay %s &", av_files[i]);
			system(buf);//执行命令
			//system("killall -18 madplay");
		}
		else if (x > 100 && x <= 150 && y >= 430 && y <= 480)//暂停
		{
			system("killall -19 madplay");
		}
		else if (x > 150 && x <= 200 && y >= 430 && y <= 480)//下一首
		{
			i++;
			if (i == 3)
			{
				i == 0;
			}
			sprintf(buf, "madplay %s &", av_files[i]);
			system(buf);//执行命令
		}
		else if (x >= 700 && x <= 750 && y >= 430 && y <= 480)//增音量
		{
			system("killall -9 madplay");
			value++;
			sprintf(buf, "madplay -a %d %s &", value, av_files[i]);
			system(buf);
		}
		else if (x >= 750 && x <= 800 && y >= 0 && y <= 430)//减音量
		{
			system("killall -9 madplay");
			value--;
			sprintf(buf, "madplay -a %d %s &", value, av_files[i]);
			system(buf);
		}
		else if (x>=0&&x<=50&&y>=0&&y<=50)//静音
		{
			printf(buf, "madplay -a -175 %s &",  _files[i]);
			system(buf);
		}
		else if()//关机
		{
			system("killall -9 madplay");
		}
		

	}
		munmap(lcd_ptr, 800 * 480 * 4);
		close(ts_fd);
		close(lcd_fd);


		return 0;
	
}
