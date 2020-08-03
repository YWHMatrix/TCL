//点击和滑动触摸屏，并获取坐标
#include "get_xy.h"
int get_xy(int *x, int *y)
{
	struct input_event ts;
	int x_read = 0, y_read = 1;
	
	while (1) {
		read(ts_fd, &ts, sizeof(ts));
		
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