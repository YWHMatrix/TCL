//开机动画
#include"gif.h"

int gif()//开机动画 259
{
	int i = 0;
	char buf[1024];

	for (i = 0; i < 129; i++) {
		//printf("%s\n", buf);
		if (i >= 0 && i < 10) {
			sprintf(buf, "boot/IMG0000%d.jpg", i);
		}else if (i >= 10 && i < 99) {
			sprintf(buf, "/bootIMG000%d.jpg", i);
		}
		else if (i >= 100 && i < 999)
		{
			sprintf(buf, "boot/IMG000%d.jpg", i);
		}
		
		lcd_draw_jpg(150, 40,buf, NULL, 0, 0);
		usleep(30000);
	}
}