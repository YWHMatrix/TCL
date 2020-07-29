//音乐播放器
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int music()
{
	lcd_draw_jpg((0,0"beijing.jpg",NULL,0,0);
	char array[10][1024] = { "1.jpg", "2.jpg", "3.jpg","4.jpg","5.jpg","6.jpg","7.jpg","8.jpg" };
	lcd_draw_jpg(0, 430, array[0], NULL, 0, 0);//上一首
	lcd_draw_jpg(50, 430, array[1], NULL, 0, 0);//播放
	lcd_draw_jpg(100, 430, array[2], NULL, 0, 0);//暂停
	lcd_draw_jpg(150, 430, array[3], NULL, 0, 0);//下一首
	lcd_draw_jpg(700, 430, array[4], NULL, 0, 0);//增音量
	lcd_draw_jpg(750, 430, array[5], NULL, 0, 0);//减音量
	int value = 18;//音量 -175 to 18
	int i = 0;
	char buf[2048];
	char av_files[10][1024] = { "1.mp3", "2.mp3", "3.mp3" };
	int x, y;
    int value = 18;//音量 -175 to 18
	int i = 0;
	char buf[2048];
	char av_files[10][1024] = { "1.mp3", "2.mp3", "3.mp3" };
	int x, y;
	while (1) {
		get_xy(&x, &y);
		printf("(%d, %d)\n", x, y);
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
}