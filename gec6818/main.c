#include <stdio.h>
int main(void)
{
	
	//1，设备的初始化
	dev_init();
	
	//2，功能区
	video();

	//3，设备的卸载
	dev_uninit();

	return 0;
}
