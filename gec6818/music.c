//音乐播放器
#include "music.h"
int music()
{
	lcd_draw_jpg(700,0, "out.jpg",NULL, 0, 0);
	char array[10][1024] = { "music/1.jpg", "music/2.jpg", "music/3.jpg","music/4.jpg","5music/.jpg","music/6.jpg","music/7.jpg" };
	lcd_draw_jpg(0,0,array[6],NULL,0,0);     //背景图
	lcd_draw_jpg(0, 380, array[0], NULL, 0, 0);//上一首
	lcd_draw_jpg(100, 380, array[1], NULL, 0, 0);//播放
	lcd_draw_jpg(200, 380, array[2], NULL, 0, 0);//暂停
	lcd_draw_jpg(300, 380, array[3], NULL, 0, 0);//下一首
	lcd_draw_jpg(400, 380, array[4], NULL, 0, 0);//增音量
	lcd_draw_jpg(500, 380, array[5], NULL, 0, 0);//减音量
	int i = 0;
	char buf[2048];
	char av_files[10][1024] = { "music/1.mp3", "music/2.mp3", "music/3.mp3" };
	int x, y;
    int value= 18;//音量 -175 to 18
	while (1) {
		get_xy(&x, &y);
		printf("(%d, %d)\n", x, y);
		if (x >= 0 && x <= 100 && y >= 380 && y <= 480)//上一首
		{
			i--;
			if (i == -1)
			{
				i = 2;
			}

			sprintf(buf, "madplay %s &", av_files[i]);
			system(buf);//执行命令
		}
		else if (x > 100 && x <= 200 && y >= 380 && y <= 480)//播放
		{
			sprintf(buf, "madplay %s &", av_files[i]);
			system(buf);//执行命令
			//system("killall -18 madplay");
		}
		else if (x > 200 && x <= 300 && y >= 380 && y <= 480)//暂停
		{
			system("killall -19 madplay");
		}
		else if (x > 300 && x <= 400 && y >= 380 && y <= 480)//下一首
		{
			i++;
			if (i == 3)
			{
				i == 0;
			}
			sprintf(buf, "madplay %s &", av_files[i]);
			system(buf);//执行命令
		}
		else if (x >= 400 && x <= 500 && y >= 380 && y <= 480)//增音量
		{
			system("killall -9 madplay");
			value++;
			sprintf(buf, "madplay -a %d %s &", value, av_files[i]);
			system(buf);
		}
		else if (x >= 500 && x <= 600 && y >= 380&& y <= 380)//减音量
		{
			system("killall -9 madplay");
			value--;
			sprintf(buf, "madplay -a %d %s &", value, av_files[i]);
			system(buf);
		}
		if(x>=7&&x<=800&&y>=0&&y<=0)
		{
			break;
		}

    }
		return 0;
}