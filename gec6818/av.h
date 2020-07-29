#ifndef __AV_H_
#define __AV_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

extern int av_fd;

//sprintf(play_cmd,"mplayer   %s  -slave  -input file=/tmp/fifo  -zoom -x 600 -y 430 -geometry 100:0 &",mv_name[count]);
//system(play_cmd);


void mplayer_init();
void send_cmd(char *cmd);
int res_play();
int pause_playback();
int stop_play();
int vol_up();
int vol_down();
int fast_forward();
int my_rewind();
int mute();

#endif
