#ifndef __DEV_INIT_H_
#define __DEV_INIT_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <strings.h>
#include <string.h>
#include <sys/mman.h>


extern int lcd_fd,ts_fd;
extern int *lcd_ptr;

int dev_init();


#endif
