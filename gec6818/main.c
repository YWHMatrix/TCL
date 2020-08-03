#include <stdio.h>
#include <stdio.h>
#include "lcdjpg.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <linux/input.h>
#include "dev_init.h"
#include "dev_uninit.h"
#include "photo.h"
#include "video.h"
#include "game2048.h"
#include "get_xy.h"
#include "music.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>



int ts_fd, lcd_fd;
int* lcd_ptr;
int av_fd;

int sockfd, connfd;

struct sockaddr_in myself;
struct sockaddr_in other;  //来电显示

// 初始化网络
int  tcp_init()
{
	
	//1. 买电话   sockfd：未连接套接字
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	int opt = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt));
	
	//2. 绑定电话号码
	struct sockaddr_in Rose_addr;
	bzero(&Rose_addr,sizeof(Rose_addr));
	
	Rose_addr.sin_family = AF_INET;
	Rose_addr.sin_port = htons(1159);
	Rose_addr.sin_addr.s_addr = htonl(INADDR_ANY); //可以接受任何地址的数据
	
	//inet_pton(AF_INET,argv[1],&Rose_addr.sin_addr);
	
	bind(sockfd,(struct sockaddr *)&Rose_addr,sizeof(Rose_addr));
	
	//3. 设置铃声   sockfd: 监听套接字
	listen(sockfd,5);
	
	return  sockfd;
	
}

void *read_app_data(void * arg)
{
    pthread_detach(pthread_self());
    printf("read app data\n");

	int ret;
	//客户端地址信息
	struct sockaddr_in client_addr={0};
	int len = sizeof(client_addr);
	//mplayer_init();
	//等待客户端的请求
	connfd = accept(sockfd,(struct sockaddr *)&client_addr,&len);

	if (connfd > 0) {
        printf("link succ!\n");
    }
	
	char buf[1024] = {0};

	//输出对方的IP地址信息
	printf("client connected [%s:%d]\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
	
	while (1) {
		bzero(buf,100);
		
		recv(connfd,buf,sizeof(buf),0);
		printf("from : %s\n",buf);
		
		if (strncmp(buf, "video", 5) == 0) {
			system("mplayer   video/12.avi  -zoom -x 600 -y 380 -geometry 100:0 &");
		}
		
	}
	
	pthread_exit(NULL);
}



int main()

{
	//1，设备的初始化
	dev_init();
       tcp_init();
	pthread_t tid;
	
	pthread_create(&tid, NULL, read_app_data, NULL);
	

	while (1)
	{
          
     lcd_draw_jpg(0, 0,"zm.jpg",NULL,0,0);    
     lcd_draw_jpg(200, 190,"photo.jpg",NULL,0,0);
     lcd_draw_jpg(300, 190,"game.jpg",NULL,0,0);
     lcd_draw_jpg(500, 190,"video.jpg",NULL,0,0);
     lcd_draw_jpg(400, 190,"music.jpg",NULL,0,0);
     int x, y;
     get_xy(&x, &y);
	printf("(%d, %d)\n", x, y);
        if(200<=x&&300<=x&&190<=y&&y>=290)
        {
            photo();

        }
        else if (300<x&&400>=x&&190<y&&y<=290)
        {
             game2048();
        }
        else if (400<x&&500>=x&&190<y&&y<=290)
        {
             music();
        }
        else if (500<x&&600>=x&&190<y&&y>=290)
        {
             video();
     }
		 
	}
    

	 //3，设备的卸载
	dev_uninit();

	
	return 0;
}
