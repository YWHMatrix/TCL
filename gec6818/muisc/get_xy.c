#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>


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


int main(void)
{
	//1���򿪴�����
	ts_fd = open("/dev/input/event0", O_RDWR);

	if (ts_fd == -1) {
		printf("open ts device failed!\n");
		return -1;
	}
	
	int x, y;
	
	while (1) {
		get_xy(&x, &y);
		printf("(%d, %d)\n", x, y);
	}
	
	close(ts_fd);
	
	return 0;
}