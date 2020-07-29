//视频播放器
#include <stdio.h>
#include "av.h"
#include "lcdjpg.h"
#include <stdlib.h>
#include <unistd.h>
int video()
{
	int x, y;
	int count = 0;
	char play_cmd[1024];
	
	char array[12][1024] = { "1.jpg", "2.jpg", "3.jpg","4.jpg","5.jpg","6.jpg","7.jpg","8.jpg","9.jpg","10.jpg","11.jpg","12.jpg" };
	lcd_draw_jpg(0  , 0,   array[10],NULL,0,0);
	lcd_draw_jpg(0, 380, array[0], NULL, 0, 0);//上一集
	lcd_draw_jpg(100, 380, array[1], NULL, 0, 0);//快进
	lcd_draw_jpg(200, 380, array[2], NULL, 0, 0);//继续播放
	lcd_draw_jpg(300, 380, array[3], NULL, 0, 0);//暂停
	lcd_draw_jpg(400, 380, array[4], NULL, 0, 0);//快退
	lcd_draw_jpg(500, 380, array[5], NULL, 0, 0);//下一集
	lcd_draw_jpg(600, 380, array[6], NULL, 0, 0);//停止播放
	lcd_draw_jpg(0,   0,   array[7], NULL, 0, 0);//静音
	lcd_draw_jpg(0, 100,  array[8], NULL, 0, 0);//增音量
	lcd_draw_jpg(0, 200,   array[9], NULL, 0, 0);//减音量
	lcd_draw_jpg(700, 0,   array[11], NULL, 0, 0);//开机
	char mv_name[10][1024] = {"11.avi", "12.avi"};
	int i = 0,j=0;
	while (1) {
		get_xy(&x, &y);
		printf("(%d, %d)\n", x, y);
		if (x >= 0 && x < 100 && y >= 380 && y < 480) {//上一集
			i--;
			if(i==-1)
			{
				i=1;
			}
			system("killall -9  mplayer");
			sprintf(play_cmd,"mplayer   %s  -slave  -input file=/tmp/fifo  -zoom -x 600 -y 430 -geometry 100:0 &",mv_name[i]);
			system(play_cmd);
		}
		else if (x >= 100 && x < 200 && y >= 380 && y < 480) {//快进
			fast_forward();
			}	
		else if (x >= 200 && x < 300 && y >= 380 && y < 480) {//继续播放
			res_play();
			}
		else if(x >= 300 && x < 400 && y >= 380 && y < 480)	//暂停播放
		{
			pause_playback();
		}
		else if(x >= 400 && x < 500 && y >= 380 && y < 480)//快退
		{
			my_rewind();
		}
		else if(x >= 500 && x < 600 && y >= 380 && y < 480)//下一集
		{
			i++;
			if(i==2)
			{
				i=0;
			}
			system("killall -9  mplayer");
			sprintf(play_cmd,"mplayer   %s  -slave  -input file=/tmp/fifo  -zoom -x 600 -y 380 -geometry 100:0 &",mv_name[i]);
			system(play_cmd);
		}
		else if(x >= 600 && x < 700 && y >= 380 && y < 480)//停止播放
		{
			stop_play();
		}
		else if(x >= 0 && x < 100 && y >= 0 && y < 100)//静音
		{
			mute();
		}
		else if(x >= 0 && x < 100 && y >= 100 &&y <200)//加音量
		{
			vol_up();
		}
		else if(x >= 0 && x < 100 && y >= 200 && y <300)//减音量
		{
			vol_down();
		}
		else if (x >=700  && x < 800 && y >= 0 && y < 100)//开机
		{
				sprintf(play_cmd, "mplayer   %s  -slave  -input file=/tmp/fifo  -zoom -x 600 -y 380 -geometry 100:0 &", mv_name[count]);
				system(play_cmd);
		}

	}
	
	return 0;
}
