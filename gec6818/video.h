#ifndef __VIDEO_H_
#define __VIDEO_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <strings.h>
#include <string.h>
#include "lcdjpg.h"
#include "av.h"

extern int ts_fd, lcd_fd;
extern int* lcd_ptr;
extern int av_fd;

int video();
void mplayer_init();
#endif