#ifndef __MUSIC_H_
#define __MUSIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "lcdjpg.h"
#include <linux/input.h>
#include <sys/mman.h>
#include "lcdjpg.h"
int get_xy(int *x, int *y);
int music();


#endif
