#ifndef __GIF_H_
#define __GIF_H_

#include <stdio.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "lcdjpg.h"

extern int lcd_fd;
extern int* lcd_ptr;

int gif();

#endif

