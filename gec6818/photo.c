#include "photo.h"
#include "get_xy.h"

int photo()
{
    int x, y;
	int count = 0;
	char array[10][1024]={"photo/1.jpg","photo/2.jpg","photo/3.jpg","4.jpg"};
	lcd_draw_jpg(700,0, "out.jpg",NULL, 0, 0);
	while (1) {
		get_xy(&x, &y);
		printf("(%d, %d)\n", x, y);
		if (x >= 0 && x < 400 && y >= 0 && y < 480) {
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
			if(count == 4) {
				count = 0;
			}
			lcd_draw_jpg(0,0, array[count],NULL, 0, 0);
		}
		if(x>=700&&x<=800&&y>=0&&y<=0)
		{
			break;
		}
	}
		
}