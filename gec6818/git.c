//开机动画
#include <stdio.h>
#include "lcdjpg.h"
int gif()//开机动画
{
	int i = 0;
	char buf[1024];

	for (i = 0; i < 37; i++) {
		//printf("%s\n", buf);
		if (i >= 0 && i < 10) {
			sprintf(buf, "IMG0000%d.jpg", i);
		}else if (i >= 10 && i < 99) {
			sprintf(buf, "IMG000%d.jpg", i);
		}
		lcd_draw_jpg(150, 40,buf, NULL, 0, 0);
		usleep(30000);
	}
}